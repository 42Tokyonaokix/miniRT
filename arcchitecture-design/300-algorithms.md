---
title: "miniRT 設計書 300 — アルゴリズム（描画ループ・primary ray・交差判定・shading・Rodrigues）"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, design, algorithms, camera, intersection, shading]
status: draft
---

> **この章のゴール**: 1 ピクセルの色が「どんな数式で・どの順で」決まるかを掴む。データ構造は `200-data-and-modules.md`、入力 UX は `400-interaction-and-errors.md`。

## 1. 描画ループの全体像

```
for y in 0..WIN_H:
  for x in 0..WIN_W:
    ray = generate_primary_ray(camera, x, y)
    t_hit hit
    if find_closest_hit(scene, ray, &hit):    # 1 = hit、out が埋まる
      color = shade(scene, hit, ray)
    else:                                     # 0 = miss
      color = (0, 0, 0)                       # 背景は黒
    put_pixel(app, x, y, color_to_int(color))
mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0)
```

per-pixel 完結。1 ピクセル分のデータが L1 キャッシュに収まり、CPU レイトレでは最速の構造（詳細は `../study/010-shading-and-intersection-deep-dive.md`）。

## 2. Primary Ray の生成（`render/camera.c`）

### 2.1 カメラ基底（起動時 + camera rotation 後に再計算）

```c
forward = camera.forward                    /* 正規化済み入力 */
right   = normalize(cross(forward, world_up))
up      = cross(right, forward)
```

> **【特異点】**
> `forward` が `world_up = (0, 0, 1)`（Z-up）と平行になると `cross` がゼロベクトルになり `normalize` で破綻する。
> `build_camera_basis` の冒頭で検出し、`world_up = (0, 1, 0)` に切り替える:
>
> ```c
> if (fabs(dot(forward, world_up)) > 0.9999)
>     world_up = (t_vec3){0, 1, 0};
> ```

### 2.2 ピクセル → ray 方向

ピンホールカメラモデル: 全レイがカメラ位置 1 点に集まり、距離 1 にイメージプレーンがある。

```c
fov_rad = fov_deg * PI / 180.0
half_w  = tan(fov_rad / 2.0)              /* 画面右端までの半角の tan */
half_h  = half_w * (WIN_H / (double)WIN_W) /* アスペクト比補正 */

ndc_x   = (2.0 * (x + 0.5) / WIN_W) - 1.0  /* [-1, +1]、+0.5 はピクセル中心 */
ndc_y   = 1.0 - (2.0 * (y + 0.5) / WIN_H)  /* [-1, +1]、y は反転（画面 y は下向き正） */

dir     = normalize(forward
                  + right * (ndc_x * half_w)
                  + up    * (ndc_y * half_h))
ray     = { origin: camera.position, dir: dir }
```

> **【用語】`half_w = tan(fov/2)` の意味**
> miniRT の C 行 FOV は **HFOV (Horizontal FOV)**: 画面の左端から右端まで開いた角度。
> カメラから距離 1 のイメージプレーンを考えると、画面右端は `forward` から「半角 `fov/2` だけ右」の方向にある。
> 直角三角形（隣辺 = 距離 1、対辺 = `half_w`、対角 = `fov/2`）から `tan(fov/2) = half_w / 1` → `half_w = tan(fov/2)`。

> **【用語】アスペクト比補正 `half_h = half_w * (H/W)`**
> イメージプレーンの縦横比を画面 (W×H) に合わせないと、物体が横長/縦長に歪む。
> 画面 800×600 (4:3) なら `half_h = half_w * 0.75`。VFOV はここから自動的に決まる（miniRT は HFOV 固定 = Hor+ 派）。

> **【用語】NDC (Normalized Device Coordinates) と `+0.5` の意味**
> `ndc_x`, `ndc_y` は画面中心を 0、画面端を ±1 にした正規化座標。
> `+0.5` はピクセルの **中心**を取るための補正。整数座標 `(x, y)` はピクセル左上を指すので、中心を狙うには `+0.5` 足す。

### 2.3 ピクセル ↔ 方向の線形対応

`(ndc_x, ndc_y)` は「**カメラ基底 (right, up) に対する係数**」として直接効く:

```
dir = forward + ndc_x · half_w · right + ndc_y · half_h · up
```

つまり「画面座標 → ray 方向」は **完全に線形**。これが「全ピクセル独立に並列計算できる」の根拠。

最適化: `fov_rad / half_w / half_h` は毎ピクセル同じなので、`render()` の最初に 1 回だけ計算してループに渡す。

詳細な導出は `../study/009-camera-math-deep-dive.md`。

## 3. 交差判定（`intersect/`）

各形状ごとに以下のシグネチャ:

```c
double  intersect_sphere  (const t_sphere   *sp, t_ray ray, t_vec3 *normal_out);
double  intersect_plane   (const t_plane    *pl, t_ray ray, t_vec3 *normal_out);
double  intersect_cylinder(const t_cylinder *cy, t_ray ray, t_vec3 *normal_out);
```

戻り値: 最小正の `t`（`-1.0` を miss として扱う）。`normal_out` には法線（ray と逆向きへ補正済み）を書く。

### 3.1 球（`ray_sphere.c`） — 二次方程式

レイ `P(t) = O + t·D` を球 `|P - C|² = r²` に代入:

```
|O + t·D - C|² = r²
→ (D·D) t² + 2 D·(O - C) t + |O - C|² - r² = 0
→ a t² + b t + c = 0
   a = D·D = 1   (D が正規化済みなら)
   b = 2 D·(O - C)
   c = |O - C|² - r²
判別式 disc = b² - 4ac
  disc < 0  → miss
  disc ≥ 0  → t = (-b ± √disc) / 2a、最小正の t を採用
```

### 3.2 平面（`ray_plane.c`） — 一次方程式

平面 `(P - P0) · N = 0` にレイを代入:

```
(O + t·D - P0) · N = 0
→ t = (P0 - O) · N / (D · N)
分母 D·N ≈ 0  → 平行で当たらない (miss)
t < EPSILON  → 背面 or 自己交差 (miss)
```

### 3.3 円柱（`ray_cylinder.c`） — 側面 + 上下キャップ

3 ケースの最小正 `t` を採用:

1. **側面**: 軸方向の成分を引いて 2D 円のレイ交差に落とす（球と同じ二次式構造）。さらに「交点の軸投影が `[0, height]` 範囲内か」をチェック
2. **上キャップ**: 平面交差 + 「交点が中心から半径以内か」チェック
3. **下キャップ**: 同上

詳細な式は `../study/010-shading-and-intersection-deep-dive.md` の plane / cylinder セクション。

### 3.4 `find_closest_hit` — 型別 intrusive list × 3 のループ

各形状を型別 intrusive linked list で持つ（ADR-0005 再改訂版）ので、3 つのリストをそれぞれ巡回する。

```c
int find_closest_hit(const t_scene *sc, t_ray ray, t_hit *out):
  best_t = INFINITY
  found  = 0

  /* 球リスト: head から next で巡回、キャスト不要 */
  for s = sc->spheres; s; s = s->next:
    t = intersect_sphere(s, ray, &normal)
    if t > EPSILON and t < best_t:
      best_t = t
      *out   = make_hit(t, ray, normal, s->color, OBJ_SPHERE, s)
      found  = 1

  /* 平面リスト */
  for p = sc->planes; p; p = p->next:
    t = intersect_plane(p, ray, &normal)
    if t > EPSILON and t < best_t:
      best_t = t
      *out   = make_hit(t, ray, normal, p->color, OBJ_PLANE, p)
      found  = 1

  /* 円柱リスト */
  for c = sc->cylinders; c; c = c->next:
    t = intersect_cylinder(c, ray, &normal)
    if t > EPSILON and t < best_t:
      best_t = t
      *out   = make_hit(t, ray, normal, c->color, OBJ_CYLINDER, c)
      found  = 1

  return found
```

`make_hit` の最後の引数（s / p / c）は **ヒットしたオブジェクト本体へのポインタ**。`t_hit.obj_ptr` に `void *` として格納されて、ADR-0006 のクリック選択や HUD ラベル描画では `obj_type` を見て該当型にキャストして使う。

> **【なぜ型別ループ × 3（ADR-0005）】**
> switch ディスパッチで「型ごとに分岐 → `intersect_*` を呼ぶ」と CPU の分岐予測が外れて遅くなる。
> 型別ループなら各ループ内では同じ関数を連続で呼ぶので分岐予測が完全に当たる。
> また BVH 拡張時は「球と円柱の 2 ループを BVH 走査に置き換える」だけで済む（平面は無限大なので別ループのまま）。
> 保持は **配列でなく intrusive linked list**: パーサー 1 パスで append、generic な `t_list` のように `void *content` 経由のキャストが不要になりホットループの可読性が上がる（ADR-0005 再改訂版）。配列のキャッシュ局所性は失うが、miniRT 規模（10〜100 個）では誤差レベル。

> **【用語】EPSILON**
> 浮動小数の誤差吸収用の小さい値（例 `1e-6`）。`t > EPSILON` は「自己交差を除外する」フィルタ。
> shadow ray の origin にも `hit.point + normal * EPSILON` のオフセットを足す（shadow acne 防止）。

## 4. シェーディング（`render/shade.c`）

mandatory は **ambient + diffuse (Lambert) + hard shadow** の 3 要素。

```c
t_color shade(const t_scene *sc, t_hit h, t_ray ray)
{
  /* (1) ambient: 周囲光、影でも見える最低限の明るさ */
  ambient  = h.color * (sc->ambient.color * sc->ambient.ratio)

  /* (2) shadow ray: hit point から光源へ飛ばす */
  L_vec    = normalize(sc->light.position - h.point)
  L_dist   = length(sc->light.position - h.point)
  shadow_ray = { origin: h.point + h.normal * EPSILON,  /* acne 防止 */
                 dir:    L_vec }

  t_hit blocker
  in_shadow = false
  if find_closest_hit(sc, shadow_ray, &blocker):
    if length(blocker.point - h.point) < L_dist:
      in_shadow = true       /* 光源より手前で何かに当たった */

  /* (3) diffuse (Lambert): 影でなければ cosθ で減衰 */
  diffuse = (0, 0, 0)
  if not in_shadow:
    cos_t = max(0.0, dot(h.normal, L_vec))
    diffuse = h.color * sc->light.ratio * cos_t

  return color_clamp(ambient + diffuse)
}
```

> **【用語】Lambert 余弦則**
> 光源から見て面が斜めに傾いていると、単位面積あたりに届く光が減る（`cosθ` に比例）。
> `θ` は「面の法線」と「面から光源への方向」の角度。
> `cos_t = max(0, dot(normal, light_dir))` で実装。負（裏向き）は 0 にクランプ。

> **【用語】hard shadow**
> 「shadow ray が他の物体に遮られたら、その点は diffuse なし」というシンプル方式。
> soft shadow（半影）は光源を面積で扱う必要があり、mandatory 範囲外。

## 5. 法線取得（`render/normal.c`）

統一型 `t_object` がないので、法線関数も型ごとに分離（ADR-0005）:

```c
t_vec3 normal_sphere  (const t_sphere   *sp, t_vec3 hit_point):
  return normalize(hit_point - sp->center)

t_vec3 normal_plane   (const t_plane    *pl, t_vec3 hit_point):
  return pl->normal

t_vec3 normal_cylinder(const t_cylinder *cy, t_vec3 hit_point):
  /* 軸投影を引いた水平成分を正規化、キャップは axis 方向 */

t_vec3 face_forward(t_vec3 normal, t_vec3 ray_dir):
  if dot(normal, ray_dir) > 0:
    return -normal               /* 内側視点対応 */
  return normal
```

各 `intersect_*` 関数が `normal_out` を計算する際に `face_forward` を必ず通す。

> **【用語】内側視点 / face_forward**
> カメラが球の内側に入ったとき、法線がレイ方向と同じ向き（外向き）だと shading がおかしくなる。
> `dot(normal, ray_dir) > 0` を検出して法線を反転することで、内側からでも正しく shading できる。
> 要件定義書 002 §10「落とし穴 #3」参照。

## 6. Rodrigues の回転公式（`math/rodrigues.c`、ADR-0002）

```c
/* v を axis 回りに angle (rad) 回転 */
t_vec3 rodrigues_rotate(t_vec3 v, t_vec3 axis, double angle)
{
  c = cos(angle)
  s = sin(angle)
  k = normalize(axis)
  return v * c
       + cross(k, v) * s
       + k * dot(k, v) * (1 - c)
}
```

行列を一切持たない。`t_vec3` 演算と `cos/sin` だけで完結。

> **【用語】Rodrigues の回転公式**
> 「ベクトル `v` を、軸 `k` の周りに角度 `θ` 回転させる」を、ベクトル演算だけで書ける公式。
> 行列の代わりに使うと、3×3 行列の確保・乗算が要らず、norminette の 25 行制限にも収まりやすい。
> 詳細な幾何導出と「なぜジンバルロックが起きないか」は `../study/008-rotation-deep-dive.md`。

回転の適用先（誰の何を回すか）は `400-interaction-and-errors.md` §6 の表を参照。

## 関連

- データ型: `200-data-and-modules.md`
- 入力 UX: `400-interaction-and-errors.md`
- 数学の深掘り: `../study/008` (回転), `../study/009` (カメラ), `../study/010` (shading/交差)
- ADR: `../adr/0002-transform-rodrigues.md`, `../adr/0005-per-type-structs-and-arrays.md`
