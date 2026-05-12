---
title: "miniRT 設計書 500 — 実装順序とオープン課題"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, design, roadmap, open-questions]
status: draft
---

> **この章のゴール**: Phase A → H までの順番と、設計時点で決め切れない検討事項を一覧化する。

## 1. 実装順序（Phase A 〜 H）

```
Phase A: 環境準備 (12h)
  1. MiniLibX サンプル動作確認、環境セットアップ
  2. 縞模様テスト・単色塗りで pixel/window が動くこと確認

Phase B: 数学・型 (8h)
  3. t_vec3 / t_color / t_ray + 演算関数
  4. ユニットテスト（tests/ で OK）

Phase C: パーサー骨格 (12h、ADR-0005)
  5. parse_scene: gnl で 1 行ずつ読み、先頭トークンで dispatch
  6. parse_ambient / camera / light（local seen_a/c/l で重複検出）
  7. parse_sphere / plane / cylinder（malloc + sphere_append/plane_append/cylinder_append で型別 intrusive list に append）
  8. 範囲チェック・必須欠落チェック（EOF 後に seen_a/c/l を見る）
  9. error_exit と行番号トラッキング

Phase D: 描画基盤 (8h)
  10. mlx 初期化、image 書き込み、main から固定色描画
  11. generate_primary_ray + 方向ベクトルを色化してグラデ確認

Phase E: 形状ごとに描画 (26h)
  12. ray_sphere → ハードコード球を白く描画
  13. ambient → 暗い球
  14. diffuse → 立体感のある球
  15. shadow ray → 影
  16. ray_plane → 床と球
  17. ray_cylinder（無限 → 高さ → キャップ）

Phase F: transform & 内部視点 (14h)
  18. rodrigues_rotate 単体実装 + テスト
  19. 内部視点（face_forward）対応とテストシーン確認
  20. world_up 特異点対応

Phase G: 対話操作 — keyboard + intent 層 (+10〜14h、ADR-0007)
  21. selection state + selection_next（CAMERA → LIGHT → spheres → planes → cylinders の巡回）
  22. apply_translate_* / apply_rotate_* （型別の pure な scene mutation）
  23. intents.c: intent_translate / intent_rotate / intent_select_* /
                 intent_request_render / intent_quit
  24. key_bindings dispatch（keycode → 該当 intent 呼び出し）
  25. 再描画トリガー（dirty フラグ + intent_request_render の戦略選択）
  26. キー bindings の OS 差対応 (#ifdef)

Phase G+: 対話操作 — mouse (+3〜5h、ADR-0006)
  27. mouse_bindings: press / motion / release
  28. selection_pick (click → find_closest_hit → intent_select_object)
  29. drag → intent_rotate を 2 回（yaw + pitch）呼ぶ。release で intent_request_render
  30. drag_moved 判定 (CLICK_THRESHOLD)

Phase H: 仕上げ (24h)
  31. norminette 全パス
  32. valgrind / leaks 0
  33. README.md (英語) 作成
  34. テストシーン .rt 集を test_scenes/ に整備
  35. defense Q&A 練習
```

合計 **127〜133h**（Phase C を 1 パス化で -4h、Phase G に intent 層追加で +2h）。期間 2026-05-17 〜 2026-05-31 の 2 週間に収まる見込み。

## 2. オープン課題

実装着手後に決定する項目。決まったら ADR を起こす。

### 2.1 reset (R キー) の実装

- 候補 A: パース直後の `t_scene` をディープコピーして `t_app->scene_initial` に保持、R で memcpy で戻す
- 候補 B: 各 transform 操作を逆操作のスタックに積み、R で巻き戻す
- 候補 C: R キー自体を実装しない（再起動で対応）

### 2.2 再描画パフォーマンス（決定済み: defer + 3 トリガ）

800×600 で物体 30 個だと **5〜10 秒/frame** の見込み。OS の key auto-repeat（押しっぱなしで KeyPress が 30 回/秒繰り返される）と組み合わさると、**即時 render は物理的に不可**（1 秒長押しで 30 event × 5〜10s = 150〜300s ブロック）。

**結論**: dirty + defer + 3 トリガで確定。

- mutate 系 intent は `a->input.dirty = 1` + `last_event_ms = now` を立てるだけ（μs で完了）
- 実 render は 3 トリガで発火:
  1. **idle auto-render**: `mlx_loop_hook` で「500ms 何も入力がない」を検出して render
  2. **SPACE**: 「今すぐ描いて」の明示トリガ
  3. **mouse release**: click / drag 直後に結果を見せる

### 残るチューニング項目（実機調整）

- **idle 閾値 500ms** が体感的に妥当か（短すぎると連続操作中に余計な render、長すぎると "止まったのに描かれない" 不快感）
- **mlx_loop_hook の呼ばれる頻度** が OS で異なるかもしれない、idle 検出が機能するか確認
- **render 中に来た event** をどう扱うか（mlx_loop は handler 中は新 event を queue しない仕様なら問題なし、queue されるなら 1 回の render 完了後に古い event が処理される）

詳細実装は `400-interaction-and-errors.md` §7。

### 2.3 HUD（選択中ラベル）

- 画面端に `[CAM]` `[LGT]` `[OBJ #2 sp]` のようなラベルを描画するか
- 実装するなら `mlx_string_put`（フォントは OS 依存・leak リスク）か image 内に色矩形
- 任意機能、評価必須ではない

### 2.4 マウス感度の調整（ADR-0006）

- `MOUSE_SENSITIVITY = 0.25 deg/pixel` を実機で調整
- FPS ゲームの感覚に近づける、または defense デモで「ちょうど良く」感じる値にチューニング

### 2.5 click vs drag の閾値（ADR-0006）

- `CLICK_THRESHOLD = 5px` の妥当性
- マウスのジッターで意図しない drag 判定にならないか

### 2.6 マウス座標取得の OS 差

- Linux: `mlx_mouse_get_pos(mlx, win, &x, &y)` あり
- macOS minilibx_opengl: 関数があるかバージョン差
- 必要ならハンドラー引数の `(x, y)` だけで完結させる（自分で `last_x/y` を保持）

### 2.7 transform_apply 時のカメラ基底再計算

- camera.forward が変わったら right / up を再計算 → どこで呼ぶか
- 案: `transform_apply` 内で SEL_CAMERA かつ rotate なら `build_camera_basis` 再呼び出し（drag も同様）

### 2.8 norminette と Rodrigues の 25 行制限

- `rodrigues_rotate` 本体は 25 行に収まる
- 変換適用全体は 1 関数で収まらない → `apply_rotate_camera`, `apply_rotate_object`, `apply_rotate_object_by_kind` のように分割

## 3. 次にやること

1. 設計書 003-architecture/ を二人でレビュー
2. 必要なら ADR を追加・修正
3. Phase A 着手前に MiniLibX 環境確認（要件定義書 002 §13.2）
4. 実装中に決まったオープン課題は ADR を起こして反映

## 関連

- 全体像: `100-overview.md`
- 入力 UX: `400-interaction-and-errors.md`
- ADR: `../adr/`
