---
title: "miniRT 設計書 610 — 使用可能関数チートシート"
date: 2026-05-13
project: 42-projects/03-minirt
tags: [42, raytracer, cheatsheet, allowed-functions]
status: draft
---

> **この章のゴール**: miniRT で「何を使ってよくて、何を避けるべきか」を一目で確認する。

## 1. 結論

miniRT で mandatory の実装に使える外部関数は、PDF に明記された次の範囲。

- `open`
- `close`
- `read`
- `write`
- `printf`
- `malloc`
- `free`
- `perror`
- `strerror`
- `exit`
- `gettimeofday()`
- **math library の全関数**
- **MiniLibX の全関数**
- **libft** は使用可

## 2. 実装でよく使う関数

### ファイル I/O

| 関数 | 使いどころ |
|---|---|
| `open` | `.rt` ファイルを開く |
| `read` | 1 行ずつ or バッファで読み込む |
| `close` | ファイルを閉じる |

### 標準出力・エラー

| 関数 | 使いどころ |
|---|---|
| `write` | `Error\n` の固定出力 |
| `printf` | デバッグや一時確認 |
| `perror` | システムエラーの補助表示 |
| `strerror` | `errno` の文章化 |
| `exit` | 正常終了 / 異常終了 |

### メモリ

| 関数 | 使いどころ |
|---|---|
| `malloc` | scene / object / token の確保 |
| `free` | cleanup での解放 |

### 時刻

| 関数 | 使いどころ |
|---|---|
| `gettimeofday()` | FPS 計測、簡易タイマー、double-click 判定など |

## 3. math library でよく使うもの

PDF 上は **math library の全関数が許可**。miniRT では特に次を使うことが多い。

| 関数 | 用途 |
|---|---|
| `sqrt` | ベクトル長、正規化 |
| `sin` / `cos` | Rodrigues 回転、角度計算 |
| `tan` | FOV から投影面を作る |
| `fabs` | 0 判定の誤差吸収 |
| `pow` | 将来の specular / falloff |
| `min` / `max` 系は標準 math にはない | 自前 helper で用意する |

### miniRT での実用メモ

- レイの正規化には `sqrt` が必須
- カメラ回転は `sin` / `cos` が中心
- 交差判定の判定誤差は `fabs` と EPSILON で吸収する
- 乗算や clamping は自前関数で足すほうが読みやすい

## 4. MiniLibX でよく使うもの

### 初期化・描画

| 関数 | 用途 |
|---|---|
| `mlx_init` | ライブラリ初期化 |
| `mlx_new_window` | ウィンドウ作成 |
| `mlx_new_image` | 描画先画像の作成 |
| `mlx_get_data_addr` | 画像バッファの生ポインタ取得 |
| `mlx_put_image_to_window` | 画像をウィンドウへ反映 |

### 終了・破棄

| 関数 | 用途 |
|---|---|
| `mlx_destroy_window` | ウィンドウ破棄 |
| `mlx_destroy_image` | 画像破棄 |
| `mlx_destroy_display` | Linux 系での終了補助 |

### イベント

| 関数 | 用途 |
|---|---|
| `mlx_key_hook` | キー入力 |
| `mlx_mouse_hook` | マウス入力 |
| `mlx_hook` | close / motion / release など汎用イベント |
| `mlx_loop_hook` | 毎フレーム処理 |
| `mlx_loop` | イベントループ開始 |

## 5. libft の使いどころ

libft は許可されているので、入力パースや文字列処理は積極的に使ってよい。

よく使う候補:

- `ft_strlen`
- `ft_strdup`
- `ft_substr`
- `ft_split`
- `ft_strchr`
- `ft_strncmp`
- `ft_atoi`
- `ft_isdigit`
- `ft_isspace` 相当は自前で用意してもよい

## 6. 使わないほうがよいもの

mandatory の実装方針としては、次は避ける。

- `fork`, `execve`, `pipe` などのプロセス系
- `pthread_*` などのスレッド系
- `stat`, `opendir` などのファイルシステム探索系
- 任意の外部ライブラリ追加

## 7. すぐ参照したい判断基準

- ファイルを読む: `open` + `read`
- 数値計算: `math.h`
- 画面に出す: MiniLibX
- テキスト処理: `libft`
- エラー終了: `write` + `free` + `exit`

## 8. 実装時の注意

- `math.h` を使うときは Makefile に `-lm` が必要
- MiniLibX は OS によりリンク指定が変わる
- 使えるからといって何でも使わず、`libft` と自前 helper を優先すると依存が整理しやすい
