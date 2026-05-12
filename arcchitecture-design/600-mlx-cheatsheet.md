---
title: "miniRT 設計書 600 — MiniLibX 関数チートシート"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, minilibx, cheatsheet]
status: draft
---

> **この章のゴール**: コーディング中に手元でさっと参照する API + 使う順。詳しい解説と例は `../study/004-minilibx-api.md`。

## 1. 起動シーケンスでの使う順

```c
mlx        = mlx_init();                                         /* (1) 初期化 */
win        = mlx_new_window(mlx, WIN_W, WIN_H, "miniRT");        /* (2) ウィンドウ */
img        = mlx_new_image(mlx, WIN_W, WIN_H);                   /* (3) 画像バッファ */
addr       = mlx_get_data_addr(img, &bpp, &line_len, &endian);   /* (4) ピクセル書き込み用 addr */

render(...);                                                     /* (5) ピクセル書き込み + put_image_to_window */

mlx_key_hook(win, on_key, &app);                                 /* (6a) キー */
mlx_hook(win, 4, 0, on_mouse_press,   &app);                     /* (6b) マウス押下 */
mlx_hook(win, 5, 0, on_mouse_release, &app);                     /* (6c) マウス離す */
mlx_hook(win, 6, 0, on_mouse_motion,  &app);                     /* (6d) マウス移動 */
mlx_hook(win, 17, 0, on_close, &app);                            /* (6e) ✕ ボタン */

mlx_loop(mlx);                                                   /* (7) イベント待ち（return しない）*/
```

## 2. API シグネチャ一覧

### 起動・終了

```c
void   *mlx_init(void);
void   *mlx_new_window(void *mlx, int w, int h, char *title);
int     mlx_destroy_window(void *mlx, void *win);
int     mlx_destroy_image (void *mlx, void *img);
int     mlx_destroy_display(void *mlx);   /* Linux のみ */
```

### 画像バッファ（miniRT の心臓）

```c
void   *mlx_new_image(void *mlx, int w, int h);
char   *mlx_get_data_addr(void *img, int *bpp, int *line_len, int *endian);
int     mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y);
```

ピクセル書き込みは `addr` に **直接 32-bit 書き込み**:

```c
void put_pixel(t_app *a, int x, int y, int color /* 0x00RRGGBB */)
{
    char *dst = a->render.addr + y * a->render.line_len + x * (a->render.bpp / 8);
    *(unsigned int *)dst = color;
}
```

### イベント

```c
int     mlx_key_hook   (void *win, int (*f)(int keycode, void *param), void *param);
int     mlx_mouse_hook (void *win, int (*f)(int button, int x, int y, void *param), void *param);
int     mlx_hook       (void *win, int event, int mask, int (*f)(), void *param);
int     mlx_loop_hook  (void *mlx, int (*f)(void *param), void *param);
int     mlx_loop       (void *mlx);
```

### イベントコード（Linux X11）

| 番号 | 意味 |
|---|---|
| 2 | キー押下 |
| 3 | キー離す |
| 4 | マウスボタン押下 |
| 5 | マウスボタン離す |
| 6 | マウス移動 (motion) |
| 17 | ウィンドウ閉じる |

### マウス位置取得（任意）

```c
int     mlx_mouse_get_pos(void *mlx, void *win, int *x, int *y);  /* OS 差注意 */
```

handler 引数の `(x, y)` で代替できるので、ADR-0006 の実装では `mlx_mouse_get_pos` に依存しない設計を推奨。

## 3. OS 差

| 項目 | Linux | macOS |
|---|---|---|
| リンク | `-lmlx -lXext -lX11` | `-lmlx -framework OpenGL -framework AppKit` |
| ESC keycode | 65307 | 53 |
| 矢印 ↑ | 65362 | 126 |
| 矢印 ↓ | 65364 | 125 |
| `mlx_destroy_display` | 存在する | 存在しない |
| マウス座標 API | `mlx_mouse_get_pos` 有 | バージョン差あり、handler 引数の `(x, y)` で代替推奨 |

両 OS 対応:
```c
#ifdef __linux__
    mlx_destroy_display(a->render.mlx);
#endif
```

## 4. よくある事故

| 症状 | 原因 |
|---|---|
| 閉じるボタンで segfault | `mlx_hook(win, 17, ...)` を登録していない |
| 1 ピクセルずつ描画して数十秒かかる | `mlx_pixel_put` を使っている（NG）。`mlx_new_image` + `put_pixel` + `mlx_put_image_to_window` が正解 |
| 何も描画されない | `mlx_put_image_to_window` を `mlx_loop` の **後** に書いている（loop は return しない）|
| 色がおかしい | アドレス計算ミス or `0xRRGGBB` 形式でない。`int red = 0x00FF0000` で赤一色になるか確認 |
| valgrind が大量に leak 報告 | MiniLibX 自体の leak。`mlx.supp` で suppress |

## 5. デバッグ最初の 2 つ

1. **縞模様テスト**: 赤緑の縦縞が出れば pixel 書き込み・カラー指定・ウィンドウ転送の 3 つが OK
2. **方向ベクトル可視化**: `ray.dir` の各成分を `[0,255]` に詰めて RGB で描画。グラデが出れば camera が動いている

詳細は `../study/004-minilibx-api.md` §7。

## 関連

- 詳細解説: `../study/004-minilibx-api.md`
- 設計書 全体像: `100-overview.md`
- 入力 UX: `400-interaction-and-errors.md`
