---
title: "miniRT 設計書 003-architecture — Index"
date: 2026-05-12
project: 42-projects/03-minirt
tags: [42, raytracer, design, index]
status: draft
---

## 概要

miniRT の **実装ブループリント**。要件定義書 `../002-requirements-spec.md` に対応する設計書を、章ごとに分割して保守する。元の単一ファイル版は `../003-architecture-design.md`（参考用、内容はこちらに移行）。

設計判断は `../adr/` に分離。

## 主要意思決定（ADR）

| ADR | 決定 | 状態 |
|---|---|---|
| ~~[ADR-0001](../adr/0001-object-representation-tagged-union.md)~~ | ~~object 表現 = タグ付き union~~ | Superseded by ADR-0005 |
| [ADR-0002](../adr/0002-transform-rodrigues.md) | transform 実装方式 = Rodrigues 軽量 | 採用 |
| ~~[ADR-0003](../adr/0003-object-storage-linked-list.md)~~ | ~~object 保持 = 連結リスト~~ | Superseded by ADR-0005 |
| [ADR-0004](../adr/0004-transform-ux-interactive.md) | transform UX = runtime 対話操作（keyboard） | 採用 |
| [ADR-0005](../adr/0005-per-type-structs-and-arrays.md) | object 表現 + 保持 = 型別構造体 + 型別 linked list | 採用（2026-05-12 更新） |
| [ADR-0006](../adr/0006-mouse-input-selection-and-camera-look.md) | mouse input = click 選択 + camera drag-look | 採用 |
| [ADR-0007](../adr/0007-input-intent-abstraction.md) | input layer = intent abstraction（入力源とロジック分離） | 採用 |

## 読む順ガイド

| 立場 | 読む順 |
|---|---|
| はじめての人 | `100-overview` 通読 → 自分が触る章だけ深掘り |
| データ・モジュール構成を触る人 | `200-data-and-modules` |
| レンダリングを書く人 | `300-algorithms` + `600-mlx-cheatsheet` |
| 入力・UI を書く人 | `400-interaction-and-errors` + `600-mlx-cheatsheet` |
| 計画を見たい人 | `500-roadmap` |

## ファイル一覧

| ファイル | 内容 |
|---|---|
| [100-overview.md](./100-overview.md) | 目的・スコープ・工数 / 3層×処理フロー（Mermaid）/ 起動シーケンス / 対話ループ |
| [200-data-and-modules.md](./200-data-and-modules.md) | 全データ型（vec3 / shape / scene / app）/ 層構成 / ディレクトリ / メモリ所有権 |
| [300-algorithms.md](./300-algorithms.md) | 描画ループ / primary ray（half_w・アスペクト・特異点）/ 交差判定（球・平面・円柱）/ shading / 法線 / Rodrigues |
| [400-interaction-and-errors.md](./400-interaction-and-errors.md) | 入力モデル / selection / キーボード / マウス click + drag / エラー方針 |
| [500-roadmap.md](./500-roadmap.md) | Phase A〜H の実装順 / オープン課題 |
| [600-mlx-cheatsheet.md](./600-mlx-cheatsheet.md) | MiniLibX API シグネチャ + 使う順 + OS 差 |

## 関連ドキュメント

- 要件定義: `../001-requirements-and-knowledge.md`, `../002-requirements-spec.md`
- 設計セッションログ: `../004-design-session-2026-05-11.md`
- 学習ノート: `../study/`（004 mlx, 007 DOD/DDD, 008 回転, 009 カメラ, 010 shading/交差 など）
- 旧版（参考）: `../003-architecture-design.md`
- ADR: `../adr/`
