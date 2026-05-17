---
title: "miniRT 設計書 400 — 入力 UX（keyboard + mouse）・selection・エラー方針"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, design, interaction, input, error-handling]
status: draft
---

> **この章のゴール**: 「ユーザーが何を押すと、何が選ばれて、何が動くか」と「エラー時にどう死ぬか」を確定する。

## 1. 入力モデル全体像

| 入力                                            | 役割                             | 根拠       |
| --------------------------------------------- | ------------------------------ | -------- |
| キーボード（TAB / WASD / QE / 矢印 / SPACE / R / ESC） | 選択切替・translate / rotate・再描画・終了 | ADR-0004 |
| マウス左クリック                                      | object を直接選択（クリック先の物体）         | ADR-0006 |
| マウス左ドラッグ（CAMERA 選択中のみ）                        | 水平/垂直回転（FPS マウスルック）        | ADR-0006 |

操作の流れ:
```
1. TAB か左クリックで「動かしたいもの」を選ぶ
2. WASD/QE で動かす、矢印 or camera-drag で回す
3. SPACE か即時で再描画して結果を見る
```

## 1.5 アーキテクチャ: handler → intent → apply（ADR-0007）

入力デバイスごとの handler は、`a->input.selected` を見て **直接 scene を mutate するのではなく**、共通の **intent 関数群** を呼び出す。intent が `apply_*` を呼んで scene を mutate し、dirty を立てる。

```
[ key / mouse event ]
        ↓
[handler 層]   key_bindings.c / mouse_bindings.c
        ↓     （keycode / mouse event を該当 intent に dispatch）
[intent 層]   intent_translate / intent_rotate / intent_select_* /
              intent_request_render / intent_quit
        ↓     （a->input.selected を見て scene を mutate、dirty を立てる）
[apply 層]    apply_translate / apply_rotate / selection_*
        ↓
[render]      a->input.dirty == 1 のとき render()
```

### intent 関数一覧（`interact/intents.c`）

```c
void intent_translate     (t_app *a, t_vec3 delta);
void intent_rotate        (t_app *a, t_vec3 axis, double angle);
void intent_select_next   (t_app *a);
void intent_select_object (t_app *a, t_obj_type type, void *obj_ptr);
void intent_request_render(t_app *a);
void intent_quit          (t_app *a);
```

intent 関数の責務:
- `a->input.selected` を読んで「何を動かすか」を判断
- 該当 object に対する `apply_translate / apply_rotate` を呼ぶ
- mutation 後の後処理（camera rotate なら `build_camera_basis`、すべての mutate で `a->input.dirty = 1`）

> **【なぜ intent 層を挟むか（ADR-0007）】**
> ① key と mouse の重複ロジックが消える（後処理は intent 内 1 箇所）、
> ② 下流テストが mlx 不要（intent を直接呼べる）、
> ③ 入力デバイス追加が容易（gamepad / スクリプトを足しても apply_* には触らない）、
> ④ 下流は入力デバイスを知らない（疎結合）。

## 2. selection の状態とサイクル

```c
typedef enum e_select_kind { SEL_NONE, SEL_CAMERA, SEL_LIGHT, SEL_OBJECT } t_select_kind;
```

- **起動時**: `SEL_CAMERA`
- **TAB**: `CAMERA → LIGHT → object[0] → object[1] → ... → object[N-1] → CAMERA → ...`
  - object の順序は parser 登録順（型別 intrusive list を `sphere → plane → cylinder` の順で走査）
  - `selection_next` の実装: 現在の `obj_ptr` を該当型にキャストして `->next` を見る。NULL なら次の型のリスト先頭へ。空リストはスキップ。
- **左クリック**: クリック先のピクセルから primary ray を 1 本飛ばし、`find_closest_hit` で `t_hit` を取得。`obj_type` / `obj_ptr` で selection を直接 `SEL_OBJECT` にセット。何も当たらなければ selection は変えない（誤クリック対策）
- **物体 0 個のシーン**: `CAMERA ↔ LIGHT` を交互にサイクル

## 3. キーボード入力（`interact/key_bindings.c`）

handler は **keycode → 該当 intent の dispatch** だけを担当する。実際の scene mutate は intent → apply 層が行う。

| キー    | 呼ぶ intent               | 引数                             |
| ----- | ----------------------- | ------------------------------ |
| ESC   | `intent_quit`           | —                              |
| TAB   | `intent_select_next`    | —                              |
| W     | `intent_translate`      | `scale(camera.forward, +STEP)` |
| S     | `intent_translate`      | `scale(camera.forward, -STEP)` |
| A     | `intent_translate`      | `scale(camera.right,   -STEP)` |
| D     | `intent_translate`      | `scale(camera.right,   +STEP)` |
| Q     | `intent_translate`      | `scale(world_up,       +STEP)` |
| E     | `intent_translate`      | `scale(world_up,       -STEP)` |
| ←     | `intent_rotate`         | `world_up, -ANGLE_STEP`        |
| →     | `intent_rotate`         | `world_up, +ANGLE_STEP`        |
| ↑     | `intent_rotate`         | `camera.right, -ANGLE_STEP`    |
| ↓     | `intent_rotate`         | `camera.right, +ANGLE_STEP`    |
| R     | `intent_reset`          | （未確定、`500-roadmap.md` §2.1）    |
| SPACE | `intent_request_render` | —                              |

```c
# define STEP        1.0          /* world units */
# define ANGLE_STEP  (M_PI / 36)  /* 5° */
```

例: `on_key`:

```c
int on_key(int kc, t_app *a)
{
    if (kc == KEY_ESC)   return (intent_quit(a), 0);
    if (kc == KEY_TAB)   return (intent_select_next(a), 0);
    if (kc == KEY_W)     return (intent_translate(a, scale(a->scene.camera.forward, +STEP)), 0);
    /* ... 他のキーも同じパターン ... */
    if (kc == KEY_SPACE) return (intent_request_render(a), 0);
    return (0);   /* 未割り当てキーは no-op */
}
```

> **【用語】キーコードの OS 差**
> ESC は Linux で 65307、macOS で 53、矢印キーも別の数字。`#ifdef __APPLE__` で切り替えるか、両方の数字を if で比較。詳細は `600-mlx-cheatsheet.md` §3。

## 4. マウス入力（`interact/mouse_bindings.c`、ADR-0006）

### 4.1 イベント登録

```c
mlx_hook(win, 4, 0, on_mouse_press,   &app);  /* event 4 = button press */
mlx_hook(win, 5, 0, on_mouse_release, &app);  /* event 5 = button release */
mlx_hook(win, 6, 0, on_mouse_motion,  &app);  /* event 6 = motion notify */
```

### 4.2 ハンドラー（intent 層を呼ぶだけ、ADR-0007）

```c
int on_mouse_press(int button, int x, int y, t_app *a)
{
  if (button != LEFT_BUTTON) return 0;
  a->input.track.drag_active  = 1;
  a->input.track.drag_last_x  = x;
  a->input.track.drag_last_y  = y;
  a->input.track.drag_moved   = 0;   /* click か drag かは release 時に判定 */
  return 0;
}

int on_mouse_motion(int x, int y, t_app *a)
{
  if (!a->input.track.drag_active) return 0;
  int dx = x - a->input.track.drag_last_x;
  int dy = y - a->input.track.drag_last_y;
  if (abs(dx) + abs(dy) > CLICK_THRESHOLD)
    a->input.track.drag_moved = 1;
  if (a->input.selected.kind == SEL_CAMERA) {
    t_vec3 world_up = {0, 1, 0};
    intent_rotate(a, world_up,             -dx * MOUSE_SENS_RAD); /* yaw */
    intent_rotate(a, a->scene.camera.right, -dy * MOUSE_SENS_RAD); /* pitch */
    /* drag 中は描画しない。dirty + last_event_ms は intent_rotate 内で更新 */
  }
  a->input.track.drag_last_x = x;
  a->input.track.drag_last_y = y;
  return 0;
}

int on_mouse_release(int button, int x, int y, t_app *a)
{
  if (button != LEFT_BUTTON) return 0;
  if (!a->input.track.drag_moved) {
    t_hit h;
    if (pick(a, x, y, &h))                          /* primary ray → find_closest_hit */
      intent_select_object(a, h.obj_type, h.obj_ptr);
  }
  a->input.track.drag_active = 0;
  intent_request_render(a);    /* click / drag どちらも結果を見せる（明示トリガ ③） */
  return 0;
}
```

### 4.3 マウスルック量のスケーリング

```c
# define MOUSE_SENSITIVITY  0.25  /* deg per pixel */
# define MOUSE_SENS_RAD     (MOUSE_SENSITIVITY * M_PI / 180.0)
# define CLICK_THRESHOLD    5     /* pixels */
```

camera 回転時の上下方向の角度は ±89° で clamp する（特異点回避）。実装方針は `intent_rotate` 内（SEL_CAMERA かつ camera.right 軸の場合）か `apply_rotate_camera` 内で行う。意図は「camera を回すなら必ずクランプ」を 1 箇所にまとめること。

感度・閾値の最終値は実機チューニング（`500-roadmap.md` §2.4-2.5）。

## 5. selection × intent の動作（matrix）

intent_translate / intent_rotate は `a->input.selected` を見て分岐する。

| 選択中      | `intent_translate(δ)` の挙動 | `intent_rotate(axis, ang)` の挙動                                             |
| -------- | ------------------------- | -------------------------------------------------------------------------- |
| CAMERA   | `camera.position += δ`    | `camera.forward = rodrigues(...)` + `build_camera_basis`（pitch ±89° clamp） |
| LIGHT    | `light.position += δ`     | **no-op**（subject 例外）                                                      |
| sphere   | `sp->center += δ`         | **no-op**（subject 例外）                                                      |
| plane    | `pl->point += δ`          | `pl->normal = rodrigues(pl->normal, axis, ang)`                            |
| cylinder | `cy->center += δ`         | `cy->axis = rodrigues(cy->axis, axis, ang)`                                |

すべての mutate ケースで `a->input.dirty = 1` を立てる（no-op 時は立てない）。

mouse click（drag なしの press → release）は selection 変更だけで scene mutate なし。`intent_select_object` 内で dirty を立てるかは未確定（HUD 実装なら立てる必要あり、なしなら不要）。

## 6. intent → apply の対応

intent 関数は **selection を判断 → 該当 apply_* を呼ぶ → 後処理** という構造。`interact/transform_apply.c` の apply 関数群は **型ごとに分かれた pure な mutation**:

| 関数 | 入力 | 挙動 |
|---|---|---|
| `apply_translate_camera`   | `t_camera *cam, t_vec3 δ` | position += δ |
| `apply_rotate_camera`      | `t_camera *cam, t_vec3 axis, double ang` | forward = rodrigues(...) + basis 再計算 |
| `apply_translate_light`    | `t_light *lt, t_vec3 δ` | position += δ |
| `apply_translate_sphere`   | `t_sphere *sp, t_vec3 δ` | center += δ |
| `apply_translate_plane`    | `t_plane *pl, t_vec3 δ` | point += δ |
| `apply_translate_cylinder` | `t_cylinder *cy, t_vec3 δ` | center += δ |
| `apply_rotate_plane`       | `t_plane *pl, t_vec3 axis, double ang` | normal = rodrigues(...) |
| `apply_rotate_cylinder`    | `t_cylinder *cy, t_vec3 axis, double ang` | axis = rodrigues(...) |

apply 関数は `t_app` を知らない（テストしやすい）。selection 判断と dirty 立ては intent 層が持つ。

## 7. 再描画タイミング（defer + 3 トリガで確定、500-roadmap §2.2）

OS の key auto-repeat（押しっぱなしで KeyPress が 30 回/秒繰り返される）と 1 描画 5〜10s の組み合わせで、即時 render 戦略は **物理的に不可**（queue が爆発する）。よって **dirty + defer + 明示トリガ** で確定。

### 動作

```
mutate 系 intent (translate / rotate / select_*):
    a->input.dirty = 1
    a->input.track.last_event_ms = now_ms()   /* gettimeofday を ms に */
    return  (μs で完了)

intent_request_render(a):
    if (a->input.dirty):
        render(a)
        a->input.dirty = 0
```

### render を発火する 3 つのトリガ

| トリガ | 呼ばれ方 | 用途 |
|---|---|---|
| ① **idle auto-render**（500ms） | `mlx_loop_hook` が「`now - last_event_ms >= 500ms` かつ `dirty == 1`」を見たら `intent_request_render` を呼ぶ | 連続操作が止まったら勝手に描く（自然な体験） |
| ② **SPACE** | `on_key` 内で `KEY_SPACE → intent_request_render` | 「今すぐ描いて」の明示トリガ |
| ③ **mouse release** | `on_mouse_release` 内で `intent_request_render` | click / drag 直後に結果を見せる |

### `mlx_loop_hook` の実装（疑似コード）

```c
int on_idle(t_app *a)
{
    if (!a->input.dirty) return 0;
    long long now = current_ms();
    if (now - a->input.track.last_event_ms >= 500)
        intent_request_render(a);
    return 0;
}
```

`mlx_loop_hook(a->render.mlx, on_idle, a)` で登録。MiniLibX は idle 時に loop_hook を呼ぶ。

> **【なぜ即時 render が不可なのか】**
> W キーを 1 秒間長押し → OS auto-repeat で KeyPress が 30 個生成され、event queue に蓄積。
> 即時 render なら 1 event = 1 render = 5〜10s ブロック。queue を捌くのに 150〜300 秒、UI が数分間固まる。
> defer + idle トリガなら 30 個の event は μs ハンドラで通り抜け、500ms 後に 1 回だけ render → 累積した最新状態が描かれる。

## 8. エラー方針（`error/exit_error.c`）

### 8.1 exit_error の責務

```c
void error_exit(const char *msg, t_app *a)
{
  ft_putendl_fd("Error", 2);
  if (msg) ft_putendl_fd((char *)msg, 2);
  if (a)   app_cleanup(a);
  exit(1);
}
```

| 経路 | msg 例 |
|---|---|
| 引数エラー | "Usage: ./miniRT <scene.rt>" / "Invalid extension" |
| ファイル I/O | "Cannot open scene file: foo.rt" |
| パーサー | "Invalid sphere format on line 12" |
| 値範囲 | "Out of range value on line 5: ambient ratio must be in [0.0, 1.0]" |
| 重複 | "Duplicate camera definition on line 18 (already defined on line 3)" |
| 必須欠落 | "Missing required element: ambient (A)" |
| メモリ | "Memory allocation failed" |

### 8.2 パーサー内エラー伝搬

- 各 `parse_*` は `int` を返す（0 = SUCCESS, 非0 = エラー、enum でコード識別）
- 行番号は `t_parse_ctx { int lineno; const char *src; }` を引数で持ち回す
- 失敗を検知したら **即 error_exit、それ以降は読まない**（fail-fast）

### 8.3 Runtime 中のエラー

- key / mouse hook の最中に malloc は発生しない（transform は in-place 更新）
- 想定外のキー / ボタンは **黙って無視**（unknown は no-op）

## 関連

- ADR: `../adr/0004-transform-ux-interactive.md`, `../adr/0006-mouse-input-selection-and-camera-look.md`, `../adr/0007-input-intent-abstraction.md`
- MiniLibX 関数: `600-mlx-cheatsheet.md`
- 未確定の項目: `500-roadmap.md` §2
