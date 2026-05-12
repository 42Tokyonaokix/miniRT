---
title: "miniRT 設計書 200 — データ構造・モジュール構成・メモリ所有権"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, design, data-structures, modules, memory]
status: draft
---

> **この章のゴール**: 「何のデータを、どこに置き、誰が解放するか」を一通り把握する。式の話は次章。

## 1. 基本型（`math/`）

```c
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;

typedef struct s_color   /* [0.0, 1.0] で保持、mlx 出力時に *255 */
{
    double  r;
    double  g;
    double  b;
}   t_color;

typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  dir;        /* 正規化済み */
}   t_ray;

typedef struct s_hit
{
    t_vec3       point;     /* world coord, t を内包 */
    t_vec3       normal;    /* ray と逆向きを向くように face_forward 済み */
    t_color      color;     /* 物体表面色（shading に使う） */
    t_obj_type   obj_type;  /* どの型に当たったか */
    void        *obj_ptr;   /* 当たったオブジェクト本体、obj_type に応じて (t_sphere *) などにキャスト */
}   t_hit;
```

`find_closest_hit` のシグネチャは `int find_closest_hit(const t_scene *s, t_ray r, t_hit *out)` で、**戻り値 1 = hit (out が埋まる) / 0 = miss (out 未定義)**。

メンバの意図:
- `point / normal / color`: shading で直接使う（ambient + diffuse + shadow ray の origin）。`t` は point に内包されてるので持たない
- `obj_type / obj_ptr`: ADR-0006 のクリック選択用。shading では参照しない。`find_closest_hit` がどの型のループ中に最小 t を更新したかを覚えておく
- miss/hit 判定は **戻り値**で行う（`int hit` のフラグは持たない、状態の二重表現を避ける）
- 物体は cleanup まで stable（runtime で追加削除しない）なのでポインタで保持して安全

## 2. 形状型（`intersect/` の入力データ）

各形状は **独立した構造体**として定義する。タグ付き union および統一型 `t_object` は使わない（ADR-0005）。

```c
typedef struct s_sphere
{
    t_vec3              center;
    double              radius;     /* 入力は直径、内部で /2 */
    t_color             color;
    struct s_sphere    *next;       /* intrusive linked list の next */
}   t_sphere;

typedef struct s_plane
{
    t_vec3              point;
    t_vec3              normal;     /* 正規化済み */
    t_color             color;
    struct s_plane     *next;
}   t_plane;

typedef struct s_cylinder
{
    t_vec3              center;
    t_vec3              axis;       /* 正規化済み */
    double              radius;
    double              height;
    t_color             color;
    struct s_cylinder  *next;
}   t_cylinder;

typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
}   t_obj_type;
```

> **【intrusive linked list】**
> next ポインタを **形状本体の中に埋め込む** スタイル。`scene->spheres` は `t_sphere *`（先頭ノード）、各ノードが `next` で繋がる。
> 巡回: `for (t_sphere *s = scene->spheres; s; s = s->next) intersect_sphere(ray, s);`

> **【用語】タグ付き union（tagged union / discriminated union）**
> 1 つの型で「sphere か plane か cylinder のどれか」を表現する C のテクニック。
> `union` でメモリを共有し、`type` フィールドで「今どれか」を識別する。
>
> **【なぜ採用しない（ADR-0005）】**
> miniRT のホットループは「数十〜数百個の物体について全ピクセルで `intersect_*` を呼ぶ」もの。
> 型別に分けて持つと、① 各ループの分岐予測が当たる（型ごとに固定関数を呼ぶ）、② BVH 拡張時に差し替えが局所化する、というメリットがある。
> タグ付き union は switch ディスパッチが必須で、分岐予測が外れやすい。
> 保持方式は「型別配列」も検討したが、パーサーが 2 パス読みになる重さを嫌い「**型別 linked list**」に決定（ADR-0005 改訂版）。さらに list 実装は libft の `t_list`（generic、`void *content`）ではなく **intrusive list（next を本体に埋め込む）** を採用（ADR-0005 再改訂）。理由: spheres list は常に t_sphere 一型なので generic 性が使われない／malloc が 1 回／キャストが消えてホットループが読みやすい。代償は追加 helper 6 関数 ≈ 30〜40 行のみ。

## 3. シーン型（`t_scene`）

```c
typedef struct s_ambient
{
    double  ratio;      /* [0.0, 1.0] */
    t_color color;
}   t_ambient;

typedef struct s_camera
{
    t_vec3  position;
    t_vec3  forward;    /* 入力された direction、正規化済み */
    t_vec3  right;      /* 起動時に build_camera_basis で計算 */
    t_vec3  up;         /* 起動時に build_camera_basis で計算 */
    double  fov_deg;
    double  yaw;        /* FPS-style 蓄積 (ADR-0004 追記、ADR-0006 で drag に必要) */
    double  pitch;      /* FPS-style 蓄積、±89° で clamp */
}   t_camera;

typedef struct s_light
{
    t_vec3  position;
    double  ratio;      /* [0.0, 1.0] */
    t_color color;      /* mandatory では未使用 */
}   t_light;

typedef struct s_scene
{
    t_ambient    ambient;
    t_camera     camera;
    t_light      light;

    /* 型別 intrusive linked list（ADR-0005 再改訂版）。パース時に 1 パス読み + append */
    t_sphere    *spheres;     /* 先頭ノード、next で繋がる */
    t_plane     *planes;
    t_cylinder  *cylinders;
}   t_scene;
```

> **【なぜ `n_*` カウンタを持たないか】**
> linked list なので「数を事前に知る必要」はパース時にもホットループでも発生しない。
> 必要な箇所（例: defense で「物体何個？」と聞かれたら）はその場で巡回カウントすれば取れる。
> 型として持つと「実体と数の同期」を維持する責任が生まれて bug の温床になりやすいので持たない。

> **【なぜ `has_a / has_c / has_l` を持たないか】**
> これらは「パース中の状態」を表すフラグで、パース完了後は使われない。
> `t_scene` に持たせると「シーンの内容」と「パースの履歴」が混ざる。
> 代わりに `parse_scene` 内の局所変数 `seen_a / seen_c / seen_l` で重複検出 + EOF 後の必須欠落チェックを行う。

## 4. アプリ全体 + selection 型（`t_app`、ADR-0007 で 3 子 struct にネスト）

`t_app` は「プログラム全体で寿命を共有するモノの集合」で、3 層アーキテクチャと一致した 3 つの子 struct を持つ:

```c
/* --- selection（intent 層が「何を動かすか」判断するための内部状態） --- */

typedef enum e_select_kind
{
    SEL_NONE,
    SEL_CAMERA,
    SEL_LIGHT,
    SEL_OBJECT
}   t_select_kind;

typedef struct s_selection
{
    t_select_kind   kind;
    t_obj_type      obj_type;   /* SEL_OBJECT 時のみ意味あり */
    void           *obj_ptr;    /* SEL_OBJECT 時、(t_sphere *) / (t_plane *) / (t_cylinder *) のいずれか */
}   t_selection;

/* --- 入力 tracking 状態（マウス drag + 共通のタイミング、ADR-0006 / ADR-0007） --- */

typedef struct s_input_track
{
    /* マウス drag tracking（マウス入力時のみ意味あり） */
    int         drag_active;       /* 1 なら drag 中 */
    int         drag_last_x;       /* 直前の motion 座標 */
    int         drag_last_y;
    int         drag_moved;        /* CLICK_THRESHOLD を超えたら 1 */

    /* idle 検出（key と mouse 両方が更新、auto-render トリガに使う） */
    long long   last_event_ms;     /* gettimeofday を ms に変換した monotonic time */
}   t_input_track;

/* --- 3 子 struct（ADR-0007） --- */

typedef struct s_input_state     /* 入力層の内部状態（ADR-0007） */
{
    t_selection     selected;
    t_input_track   track;       /* drag tracking + idle 検出（旧 t_mouse_state を拡張） */
    int             dirty;       /* 1 なら次の機会に render を呼ぶ */
}   t_input_state;

typedef struct s_render_ctx      /* インフラ：MiniLibX ハンドル + image レイアウト */
{
    void   *mlx;
    void   *win;
    void   *img;
    char   *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_render_ctx;

typedef struct s_app
{
    t_scene         scene;       /* ドメイン */
    t_render_ctx    render;      /* インフラ */
    t_input_state   input;       /* 入力層 */
}   t_app;
```

> **【なぜ 3 子 struct にネストするか（ADR-0007）】**
> `t_app` は MiniLibX hook の `void *param` 経由で各 handler に渡される「全部入りコンテキスト」。
> ① ドメイン (scene)、② インフラ (mlx 系)、③ UI/入力 (selection / mouse / dirty) は意味が違うのに、フラットに並べると同じ粒度に見えてしまう。
> 3 つに分けると 100-overview の 3 層アーキテクチャと一致し、関数に渡す引数も `(&a->input, &a->scene.camera)` のように **必要な部分だけ**渡せる。
> アクセスが `a->mouse.last_x` → `a->input.track.drag_last_x` と 1 段深くなるが、構造の明確さを優先する。

> **【dirty とは】**
> 「scene を mutate した。次の機会に render したい、けどまだ描いていない」フラグ。
> 1 描画 5〜10s なので key 連打のたびに即 render すると UI が固まる（特に OS の key auto-repeat で破滅する）。
> intent_translate / intent_rotate などの mutate 系 intent はすべて `a->input.dirty = 1` を立て、同時に `a->input.track.last_event_ms` を現在時刻で更新する。実際の render は次の 3 トリガで発火（500-roadmap §2.2 で確定）:
> ① 500ms 何も入力がなければ `mlx_loop_hook` で自動 render（last_event_ms を見て判定）
> ② SPACE キーで明示 render
> ③ マウス left release（drag/click 直後）で render

> **【last_event_ms とは】**
> idle 検出のための「最後に dirty を立てたイベントの時刻」。`gettimeofday` を ms に変換した monotonic time。
> mlx_loop_hook が「`now_ms - last_event_ms >= 500` かつ `dirty == 1`」を見て auto-render を発火する。

## 5. モジュール構成 — 3層

依存方向は **上から下の一方向**。下の層は上の層を知らない。

```
┌─────────────────────────────────────────────────┐
│ アプリ層  (miniRT 固有のオーケストレーション)   │
│  main.c / parser/ / interact/ /                 │
│  mlx/ (全部) / memory/ / error/                 │
└─────────────────┬───────────────────────────────┘
                  │ uses
                  ▼
┌─────────────────────────────────────────────────┐
│ ドメイン層  (レイトレの概念、純粋関数のみ)      │
│  intersect/ / render/                           │
│  (scene + ray → color、mlx は知らない)          │
└─────────────────┬───────────────────────────────┘
                  │ uses
                  ▼
┌─────────────────────────────────────────────────┐
│ インフラ層  (汎用の道具箱)                      │
│  math/                                          │
└─────────────────────────────────────────────────┘
```

| 層 | ディレクトリ | 役割 |
|---|---|---|
| アプリ層 | `main.c`, `parser/`, `interact/`, `mlx/` (全部), `memory/`, `error/` | 外界とつながる（ファイル / ウィンドウ / キー / マウス / 解放）。副作用あり |
| ドメイン層 | `intersect/`, `render/` | レイトレの式（交差判定・shading・法線・primary ray 生成）。`t_scene` と `t_ray` で完結、mlx を一切知らない |
| インフラ層 | `math/` | 汎用の数学。`t_scene` も `t_app` も知らない |

> **【3 層の分け方ルール】**
> 「ライブラリ単位」ではなく「**miniRT の型を知ってるか**」で分ける:
> - インフラ層 = `t_scene / t_app / t_ray` を一切知らない（vec3 演算など）
> - ドメイン層 = miniRT のレイトレ概念は知ってるが `mlx` は知らない
> - アプリ層   = 外界(mlx / file / OS)と miniRT を繋ぐ
>
> この基準で `mlx/` を見ると、`app_init.c` や `hooks.c` は `t_app *` を扱うので明確にアプリ層。`put_pixel.c` も「`addr/bpp/line_len` を受け取るだけ」とはいえ mlx の image レイアウトに張り付いた関数なので、**素直に mlx/ ディレクトリごとアプリ層**にまとめる。
>
> **【render ディレクトリと "render ループ" の分離】**
> 旧構成では `render/render.c` (ピクセルループ) と `render/shade.c` (色を計算する式) が同居していた。前者は mlx に書き込むので app 層、後者は純粋関数で domain 層 → 同じディレクトリが層をまたぐ問題があった。
> 解決: ピクセルループは `mlx/render_loop.c` に移し、`render/` には「**式だけ**」を残す（shade / normal / generate_primary_ray）。これで `render/` はテストで mlx 不要、ドメイン層として閉じる。

## 6. ディレクトリ詳細

```
srcs/
├── main.c                          /* argv → parser → mlx 起動 → loop */
├── parser/
│   ├── parse_scene.c               /* 1 行ずつ読んで dispatch */
│   ├── parse_ambient.c             /* A 行 */
│   ├── parse_camera.c              /* C 行 */
│   ├── parse_light.c               /* L 行 */
│   ├── parse_sphere.c              /* sp 行 */
│   ├── parse_plane.c               /* pl 行 */
│   ├── parse_cylinder.c            /* cy 行 */
│   └── parse_utils.c               /* split, atof, vec3 / color パース、検証 */
├── math/
│   ├── vec3_ops.c                  /* add, sub, scale, normalize, length */
│   ├── vec3_dot_cross.c            /* dot, cross */
│   ├── color_ops.c                 /* color_add, color_scale, color_mul, to_int */
│   └── rodrigues.c                 /* rodrigues_rotate(v, axis, angle) */
├── intersect/
│   ├── ray_sphere.c                /* 二次方程式、最小正の t */
│   ├── ray_plane.c                 /* 一次方程式 */
│   ├── ray_cylinder.c              /* 側面 + キャップ、高さ範囲チェック */
│   └── find_closest.c              /* 型別ループ × 3、最近接 t_hit を返す */
├── render/                         /* ドメイン層: 純粋関数のみ */
│   ├── camera.c                    /* generate_primary_ray(cam, x, y) */
│   ├── shade.c                     /* ambient + diffuse + shadow */
│   └── normal.c                    /* normal_sphere/plane/cylinder + face_forward */
├── interact/
│   ├── key_bindings.c              /* keycode → intent_* を呼ぶ */
│   ├── mouse_bindings.c            /* マウス event → intent_* を呼ぶ (ADR-0006) */
│   ├── intents.c                   /* intent_translate / intent_rotate / intent_select_* /
│   │                                  intent_request_render / intent_quit (ADR-0007) */
│   ├── selection.c                 /* selection_next / selection_pick の実装 */
│   ├── transform_apply.c           /* apply_translate / apply_rotate (型別の scene mutation) */
│   └── hud.c                       /* (任意) 選択中ラベルを画面端に描画 */
├── mlx/                            /* アプリ層: mlx 関連は全部ここ */
│   ├── app_init.c                  /* mlx_init, window, image */
│   ├── hooks.c                     /* mlx_hook 登録のみ */
│   ├── put_pixel.c                 /* image addr へ書き込み */
│   └── render_loop.c               /* render(t_app *) - 全ピクセルループ。
│                                      domain の shade/intersect を呼んで put_pixel で書く */
├── memory/
│   ├── scene_lists.c               /* sphere/plane/cylinder × append/clear の 6 関数
│   │                                  intrusive list 用 helper (ADR-0005 再改訂) */
│   ├── scene_free.c                /* spheres/planes/cylinders を clear */
│   └── app_free.c                  /* mlx_destroy_*, scene_free, mlx free */
└── error/
    └── exit_error.c                /* error_exit(msg, app *) → cleanup → exit(1) */
```

各モジュールは `minirt.h` 内のプロトタイプセクションでグルーピング。`libft.h` は別管理。

## 7. メモリ所有権モデル

### 7.1 所有関係（ADR-0005）

```
t_app  (stack on main)
  ├─ t_scene                                  (ドメイン)
  │    ├─ t_ambient, t_camera, t_light       (POD, 所有なし)
  │    ├─ t_sphere   *spheres    (intrusive list head、各ノード = malloc された t_sphere)
  │    ├─ t_plane    *planes     (同上、各ノード = malloc された t_plane)
  │    └─ t_cylinder *cylinders  (同上、各ノード = malloc された t_cylinder)
  ├─ t_render_ctx                             (インフラ)
  │    ├─ void *mlx          (mlx_init で malloc)
  │    ├─ void *win          (mlx_new_window)
  │    ├─ void *img          (mlx_new_image)
  │    └─ char *addr / int bpp / line_len / endian   (img のレイアウト記述、所有なし)
  └─ t_input_state                            (入力層)
       ├─ t_selection selected     (POD, 所有なし)
       ├─ t_input_track track      (POD, drag + idle 検出)
       └─ int dirty
```

### 7.2 解放手順

```c
void app_cleanup(t_app *a)
{
    sphere_clear(&a->scene.spheres);     /* NULL list でも安全に書く */
    plane_clear(&a->scene.planes);
    cylinder_clear(&a->scene.cylinders);
    if (a->render.img)
        mlx_destroy_image(a->render.mlx, a->render.img);
    if (a->render.win)
        mlx_destroy_window(a->render.mlx, a->render.win);
    /* Linux のみ:
       #ifdef __linux__
           mlx_destroy_display(a->render.mlx);
       #endif */
    if (a->render.mlx)
        free(a->render.mlx);
}
```

> 各 `*_clear(t_X **head)` は `while (*head) { tmp = (*head)->next; free(*head); *head = tmp; }` で書く（5 行）。intrusive なので next と本体が同じ malloc 単位 → 単純な free で完結。NULL list は while で素通り。

### 7.3 malloc 失敗時

すべての malloc 経路で:
1. それまでに確保したものを `app_cleanup(&app)` で解放
2. `error_exit("Memory allocation failed", &app)` → stderr に出力
3. `exit(1)`

`exit_error.c` 内で `app_cleanup` を呼ぶことで分散した cleanup ロジックを排除。

### 7.4 Runtime 中の所有権変化

`interact/` は scene を **mutate するだけ**で malloc/free を行わない。物体数は起動後に変動しない（パース時に確定 → runtime で transform のみ）。よって **runtime での leak リスクなし**。

## 関連

- データ型の根拠: `../adr/0005-per-type-structs-and-arrays.md`
- selection 拡張の根拠: `../adr/0006-mouse-input-selection-and-camera-look.md`
- 次章: `300-algorithms.md` — レイ生成・交差判定・shading・Rodrigues
