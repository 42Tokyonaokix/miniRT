# キー・マウス操作 ↔ 出力 対応リファレンス（サイトウ向け）

## キーボード操作

| キー | 動作 | 出力 |
| --- | --- | --- |
| `ESC` | プログラム終了（`app_free`、クリーン終了） | なし |
| `SPACE` | 選択対象を次へ巡回 | `miniRT: CAMERA: was selected` / `miniRT: LIGHT: was selected` / `miniRT: OBJECT: was selected`（OBJECT 時は続けて `miniRT: OBJ-SPHERE/OBJ-PLANE/OBJ-CYLINDER: was selected`） |
| `TAB` | TRANSLATE / ROTATE モードフラグを切替 | `miniRT: mode chanded: ROTATE MODE` または `miniRT: mode chanded: TRANSLATE MODE` ※後述の注意点あり |
| `W` / `S` | 前進 / 後退の移動量を加算（`input[T_FORWARD]` ±1） | その場では出力なし（`ENTER` で確定時にまとめて出力） |
| `A` / `D` | 左 / 右（`input[T_RIGHT]` −1 / +1） | 同上 |
| `E` / `Q` | 上 / 下（`input[T_UP]` +1 / −1） | 同上 |
| `←` / `→` | 回転量を加算（`input[R_RIGHT]` −1 / +1） | 同上 |
| `↑` / `↓` | 回転量を加算（`input[R_UP]` +1 / −1） | 同上 |
| `ENTER` | 蓄積した移動・回転を選択要素へ適用 → 再描画 → 入力バッファを 0 クリア | `print_motion` の全ダンプ（下記フォーマット） |

> `WASDQE` と矢印キーは押すたびに `input[]` に量を貯めるだけ。実際に動くのは `ENTER` を押した瞬間。選択対象が `SEL_NONE`（未選択）のときに `ENTER` を押しても何も起きない。

## マウス操作

| 操作 | 動作 | 出力 |
| --- | --- | --- |
| 左クリック（press） | クリック位置にレイを飛ばし、当たったオブジェクトを選択。当たらなければカメラを選択。座標を `buf` に保存 | `miniRT: OBJ-XXX: was selected`（命中時）/ `miniRT: CAMERA: was selected`（外した時） |
| 左ドラッグ → 離す（release） | ドラッグ量だけ選択オブジェクトを**平行移動** → 再描画 | `print_motion` の全ダンプ |
| 右クリック（press） | 左クリックと同様に選択し、座標を `buf` に保存 | 左クリックと同じ選択ログ |
| 右ドラッグ → 離す（release） | ドラッグ量だけ選択オブジェクトを**回転** → 再描画 | `print_motion` の全ダンプ |
| 中ボタン / ホイール | バインドなし | なし（無反応） |

> マウスは「押した位置」と「離した位置」の差分で動かす方式（`mouse_press` で `buf` に保存 → `mouse_release` で差分を `input[]` に入れて適用）。**ドラッグ中は反映されず、離した瞬間に確定**する。選択が `SEL_NONE` のときは release しても何も起きない。
