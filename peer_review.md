# miniRT ピアレビュー結果

**日付:** 2026-05-30
**チーム:** natakaha / kesaitou

---

## 1. Executable name — Yes

```
make  →  miniRT が生成される（re-link なし）
```

Makefile は `-Wall -Werror -Wextra` 付きで正しくコンパイル。`bonus` ターゲットは `all` を呼ぶだけで OK。

---

## 2. Configuration file — No（致命的バグ）

**テスト結果:**
```
./miniRT tests/test_files/reject_files/B_missing/B2_missing_camera.rt
→ ERR  camera  Missing required
→ INF  app_init: mlx_init  proceeded    ← ウィンドウが開いてしまう
```

**原因: `main.c:50–52`**

```c
flag = parse_scene(fd, &app.scene);   // flag = FAILURE (カメラなし)
close(fd);
flag = app_init(&app);                // ← flag を確認せず上書き！ウィンドウが開く
```

`parse_scene()` が FAILURE を返しても **その値を一切チェックせず** `app_init()` を呼び出している。全カテゴリのエラーファイル（B_missing / C_fields / C_identifier / D_numeric / E_range / F_encoding）で同様にウィンドウが開いてしまう。

サブジェクトの要件「the program returns an error and exits properly when the configuration file is misconfigured」を満たしていない。

> **この項目が No のため、ルール上はディフェンス終了・0点。**

---

## 3. Norminette

```
ray_cylinder_t.c  : TOO_MANY_LINES (25行超)
app_free.c        : BRACE_SHOULD_EOL
main.c            : LINE_TOO_LONG (82col)
find_closest.c    : SPACE_EMPTY_LINE, TAB_INSTEAD_SPC (複数)
translate_utils.c : SPACE_REPLACE_TAB, EOL_OPERATOR, TOO_FEW_TAB, MIXED_SPACE_TAB
move_objects.c    : TAB_INSTEAD_SPC
mlx_free.c        : WRONG_SCOPE_COMMENT, EMPTY_LINE_EOF
```

複数ファイルにノルムエラーあり。これも評価フラグ対象。

---

## 4. デバッグコードの残存

`ray_sphere.c`, `ray_cylinder.c`, `camera.c` に `main()` 関数がコメントアウトで残っている。評価には影響しないが、提出物としては整理が必要。

---

## 5. 描画ロジック（参考: 動作している前提での確認）

| 項目 | 評価 |
|------|------|
| 球の交差計算 | 正しい（二次方程式） |
| 平面の交差 | `ray_plane.c` 実装あり |
| 円柱の交差 | 側面 + キャップの両方を実装 |
| 影（Shadow ray） | `render_exposed_light()` で実装、影あり |
| 拡散光（Diffuse） | Lambert モデル実装あり |
| アンビエント | 実装あり |
| ESC / 赤×ボタン | `app_free()` で正しく終了、メモリ解放あり |

---

## 修正が必要な箇所（優先度順）

### 最優先（評価通過のために必須）

```c
// main.c の修正
flag = parse_scene(fd, &app.scene);
close(fd);
if (flag == FAILURE)                          // ← この3行を追加
    return (scene_free(&app.scene), EXIT_FAILURE);
flag = app_init(&app);
if (flag == FAILURE)
    return (scene_free(&app.scene), EXIT_FAILURE);
```

### 次点

- ノルムエラーの修正（特に `ray_cylinder_t.c` の TOO_MANY_LINES）
- コメントアウトされたデバッグ `main()` の削除

---

## 総評

コア実装（レイキャスト・シェーディング・パーサーのロジック）は丁寧に作られています。しかし `main.c` の **たった1行の `if (flag == FAILURE) return ...` の欠如** が、パーサー全体のエラーチェックを完全に無効化しています。修正は1〜3行で済みます。ノルムも合わせて直せば、残りの評価項目は通過できる可能性が高いです。
