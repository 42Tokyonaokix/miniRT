# Bug Report — miniRT レンダリング不具合まとめ

調査日: 2026-05-16

---

## 修正済みバグ

### [FIXED] color.c:51,55 — g/r チャンネルのクランプが逆

```c
// バグ: 正の値を全て0にしていた
if (color.g > 0)  color.g = 0;
if (color.r > 0)  color.r = 0;

// 修正後
if (color.g < 0)  color.g = 0;
if (color.r < 0)  color.r = 0;
```

**影響:** g・r チャンネルが常に 0 → 画面がほぼ真っ青になっていた（最重大）

---

### [FIXED] shade.c:78 — 拡散ライト計算で方向ベクトルを正規化していない

```c
// バグ: ライトとの距離に比例して明るさが変わる
l_scale = vec3_dot(vec3_sub(light.position, hit.point), hit.normal) * light.ratio;

// 修正後
l_scale = vec3_dot(vec3_normalize(vec3_sub(light.position, hit.point)), hit.normal) * light.ratio;
```

**影響:** 近いほど暗く・遠いほど明るくなる逆距離依存。値が 1.0 を大きく超えて白飛びする。

---

### [FIXED] render_loop.c — x リセット漏れ・描画位置・境界条件

```c
// バグ1: x を外側で初期化 → 1行目しか描画されない
x = 0;
y = 0;
while (y <= WIN_H) {
    while (x <= WIN_W) { ... x++; }
    y++;
    // x が WIN_W+1 のまま → 2行目以降の内側ループが回らない
}
mlx_put_image_to_window(..., WIN_W, WIN_H);  // バグ2: 画像がウィンドウ外に描画される

// 修正後
y = 0;
while (y < WIN_H) {
    x = 0;  // 各行の先頭でリセット
    while (x < WIN_W) { ... x++; }
    y++;
}
// main.c で mlx_put_image_to_window(..., 0, 0) を呼ぶ
```

**影響:** 1行目以外が全て黒・画像がウィンドウ外に貼られて何も見えない。

---

### [FIXED] put_pixel.c:28 — 色を1バイトしか書いていない

```c
// バグ: int(4バイト)なのに1バイトしか書かない
*(unsigned char *)pixel = color;

// 修正後
*(unsigned int *)pixel = color;
```

**影響:** RGB の上位3バイトが失われ、色が全て壊れる。

---

### [FIXED] ray_plane.c — 裏面ヒット時に法線が反転されない

```c
// 修正後: カメラレイの方向と法線が同じ向きなら反転
if (vec3_dot(ray.dir, plane->normal) > 0)
    hit.normal = vec3_scale(plane->normal, -1);
else
    hit.normal = plane->normal;
```

**影響:** 平面の裏から見ると法線がカメラと逆向き → 拡散項が常に負 → ambient のみで描画される。

---

### [FIXED] ray_cylinder_t.c:39-43 — CAPS/SIDE 判定の順序バグ

```c
// バグ: 2つのifが独立しているため後者が前者を常に上書き
if (min_t == caps_t)  *type = CAPS;
if (min_t == side_t)  *type = SIDE;  // side_t == ERRORNO のとき caps_t も -1 なら両方一致

// 修正後: caps が有効でかつ最小のときのみ CAPS に
if (min_t < 0)
    return (min_t);
if (caps_t >= 0 && min_t == caps_t)
    *type = CAPS;
else
    *type = SIDE;
```

**影響:** シリンダーキャップの法線が使われず、側面法線が使われてしまう。

---

## 未修正バグ

### [BUG-1] camera.c:28 — 右ベクトルの向きが逆（画像が左右反転）重大度: Critical

```c
// バグ: cross(forward, up) = -right (右手座標系)
camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));

// 修正案
camera->right = vec3_normalize(vec3_cross(camera->up, camera->forward));
```

**根拠:**
右手座標系で forward=(0,0,1), up=(0,1,0) のとき:
- `cross(forward, up)` = `cross((0,0,1),(0,1,0))` = `(-1,0,0)` ← 世界の -x 方向
- `cross(up, forward)` = `cross((0,1,0),(0,0,1))` = `(+1,0,0)` ← 世界の +x 方向（正しい）

スクリーン右辺に対応する NDC が `+ndc_x` → `vec3_scale((-1,0,0), +ndc_x)` → 世界の -x 方向を向く。
カメラが x=-50 にいて球が x=0 にある場合、球はスクリーン左に映るが正しくは右に映るべき。

---

### [BUG-2] camera.c:22 — カメラが -world_up 方向を向くと基底が壊れる　重大度: Medium

```c
// バグ: +world_up との一致しか検出しない
if (vec3_sq(vec3_sub(camera->forward, world_up)) < EPS * EPS)

// 修正案: 平行（同方向・逆方向とも）を検出
if (fabs(vec3_dot(camera->forward, world_up)) > 1.0 - EPS)
```

**根拠:**
`forward = (0,0,-1)` (真下) のとき:
- `world_up = (0,0,1)` との差は `(0,0,-2)` → 閾値外 → フォールバックしない
- `vec3_ver((0,0,1), (0,0,-1))` = `(0,0,1) - (0,0,1)` = `(0,0,0)` → ゼロベクトル
- `camera->up = normalize((0,0,0)) = (0,0,0)` → カメラ基底が完全に壊れる

---

### [BUG-3] shade.c:55-58 — シャドウレイが何もヒットしないとき誤って「影」判定　重大度: Medium

```c
c_hit = ray_closest_hit(light_ray, ...);
v_tmp = vec3_sub(hit.point, c_hit.point);
if (vec3_sq(v_tmp) < EPS * EPS)
    return (true);
return (false);  // ← OBJ_NONE のとき c_hit.point = (0,0,0) なので hit.point が原点付近でなければ false になる
```

シャドウレイが何もヒットしなかった場合 (`c_hit.obj_type == OBJ_NONE`)、`c_hit.point` は `ft_bzero` により `(0,0,0)` になる。
`hit.point` が原点から離れていると `v_tmp` が大きくなり、誤って「影の中」と判定される。

```c
// 修正案: OBJ_NONE なら露光（遮蔽物なし）として扱う
if (c_hit.obj_type == OBJ_NONE)
    return (true);
```

---

### [BUG-4] shade.c:40-41 — return 後の dead code　重大度: Minor

```c
static t_color	render_obj_none(t_scene scene)
{
    t_color	c;
    ft_bzero(&c, sizeof(t_color));
    return (c);
    (void)scene;   // ← 絶対に到達しない
}
```

`(void)scene` を `return` の前に移動する。

---

### [BUG-5] parse7_field2.c:45 — 浮動小数点をゼロと厳密比較　重大度: Minor

```c
// バグ: sqrt の結果をゼロと == 比較
if (vec3_abs(*vec) == 0)

// 修正案
if (vec3_sq(*vec) < EPS * EPS)
```

`vec3_abs` は `sqrt(vec3_sq(...))` を返す。浮動小数点演算の結果が正確に 0.0 になることは保証されない。

---

## 調査済みで問題なし

| 項目 | 結論 |
|---|---|
| `parse_color` の 0-255 正規化 | `/255.0` で正規化済み ✓ |
| `fill_sphere` の `radius /= 2` | subject の仕様（diameter 指定）に準拠 ✓ |
| `ray_cylinder_side_t` の射影計算 | 軸方向への垂直射影でクワドラティック正しく構築 ✓ |
| `if_valid_side_point` の高さ判定 | `vec3_hor` の差を使った軸方向距離計算は正しい ✓ |
| `if_valid_caps_point` の半径判定 | `vec3_ver` の差を使った垂直距離計算は正しい ✓ |
| `quad_min_solution` の負根処理 | 各呼び出し元が `t < 0` でガード済み ✓ |
| `cylinder_side_normal` | `vec3_ver(point - center, axis)` の正規化で正しい外向き法線 ✓ |
| `cylinder_cap_normal` | `dot(to_p, axis)` の符号でキャップ面の向きを正しく判定 ✓ |
| `color_mul` の乗算 | 0-1 範囲の double 同士の成分積として正しい ✓ |
| `camera_half_w/h` の FOV 計算 | `tan(fov/2)` で正しい half-extent ✓ |
