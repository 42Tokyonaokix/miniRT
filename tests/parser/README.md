# parser E2E tests

`tests/test_files/` のフィクスチャーファイルを使った E2E パーサーテスト。

## 構成

```
tests/
├── test_files/              ← フィクスチャー（入力ファイル）
│   ├── accept_files/         ← パース成功すべき .rt
│   └── reject_files/         ← パース失敗すべき .rt
│       ├── A_args/           ← 引数・ファイルレベルエラー
│       ├── B_missing/        ← 必須要素欠落
│       ├── B_duplicate/      ← 重複定義
│       ├── C_identifier/     ← 未知の識別子
│       ├── C_fields/         ← フィールド数不正
│       ├── D_numeric/        ← 数値形式エラー
│       ├── E_range/          ← 値域外
│       └── F_encoding/       ← エンコーディング・構造エラー
└── parser/                   ← テストスクリプト
    ├── run_tests.sh          ← メインランナー
    └── README.md             ← このファイル
```

## 使い方

### 前提

```bash
# プロジェクトルートでビルド
make
```

### 実行

```bash
# プロジェクトルートから
./tests/parser/run_tests.sh
```

スクリプト内で `cd` するので、どこから呼んでも OK。

### 出力例

```
== 1. CLI argument errors ==
  ✓ No argument is rejected
  ✓ Extra argument is rejected
  ✓ Non-existent .rt path (rejected with exit 1)

== 2. accept_files/ (all should exit 0) ==
  ✓ 01_minimal.rt
  ✓ 02_standard.rt
  ✓ 03_many_objects.rt
  ...

== 3. reject_files/A_args — argument/file errors ==
  ✓ A5_empty.rt (rejected with exit 1)
  ✓ A2_uppercase_ext.RT (rejected with exit 1)
  ...

== Summary ==
Total : 47
Pass  : 47
Fail  : 0

All tests passed.
```

## 仕組み

`miniRT` バイナリの **exit code** だけで判定:

| 期待 | バイナリの挙動 | 判定 |
|------|-------------|------|
| accept | `exit 0` | ✓ |
| accept | `exit ≠ 0` | ✗ |
| reject | `exit ≠ 0` | ✓ |
| reject | `exit 0` | ✗ |

stderr の内容（エラーメッセージ）は確認しない。「**通すべきものを通し、弾くべきものを弾く**」という大枠を保証する。

メッセージ内容まで厳密にテストしたい場合は、後述のとおり `assert_reject_with_msg` を追加できる。

## 現在のテストカバレッジ

| カテゴリ | 件数 |
|---------|------|
| CLI 引数エラー | 3 |
| accept | 7 |
| A_args reject | 5 |
| B_missing reject | 3 |
| B_duplicate reject | 3 |
| C_identifier reject | 3 |
| C_fields reject | 4 |
| D_numeric reject | 7 |
| E_range reject | 13 |
| F_encoding reject | 1 |
| **合計** | **49** |

## 拡張: 個別実行

特定のフィクスチャーだけ試すなら:

```bash
# accept ケース
./miniRT tests/test_files/accept_files/01_minimal.rt
echo "exit: $?"     # 0 期待

# reject ケース
./miniRT tests/test_files/reject_files/E_range/E1_ambient_ratio_high.rt
echo "exit: $?"     # 1 期待
```

## 拡張: stderr 内容も検証したい場合

`run_tests.sh` に以下のような関数を追加:

```bash
assert_reject_with_msg() {
    local file="$1"
    local expected_pattern="$2"
    local label="$3"
    local stderr_output
    stderr_output=$("$BINARY" "$file" 2>&1 > /dev/null)
    local code=$?
    if [ $code -ne 0 ] && echo "$stderr_output" | grep -q "$expected_pattern"; then
        printf "${G}  ✓${N} %s\n" "$label"
        PASS=$((PASS+1))
    else
        printf "${R}  ✗${N} %s (msg mismatch)\n" "$label"
        FAIL=$((FAIL+1))
    fi
}
```

例:
```bash
assert_reject_with_msg \
    "$FIXTURE_DIR/reject_files/B_missing/B1_missing_ambient.rt" \
    "Missing required: ambient" \
    "B1 prints ambient missing message"
```

## CI への組み込み

GitHub Actions / GitLab CI に組み込む場合:

```yaml
# .github/workflows/parser-tests.yml
- name: Build
  run: make
- name: Run parser tests
  run: ./tests/parser/run_tests.sh
```

スクリプトは失敗時に exit 1 を返すので、CI で自動的に検知される。

## 制約

- バイナリが parse 後すぐ exit する設計（mlx 起動前）に依存。
  もし将来 mlx 起動を main で行うようになったら、テスト用の `--parse-only` フラグなどが必要。
- stderr の内容は確認していない（exit code のみ）。詳細検証は §「stderr 内容も検証したい場合」参照。
- macOS / Linux の bash 4+ を前提（macOS デフォルトの bash 3 でも動くはず、要確認）。

## メモリリーク E2E テスト（Docker + valgrind）

`./parser_test`（parser-only バイナリ）に valgrind をかけて、各 fixture でリークを検出します。

### スクリプト

```
tests/parser/run_leak_tests.sh
```

`./miniRT` と異なり mlx を含まない最小バイナリ `./parser_test` を使うので、X11 不要・Docker で完結します。

### Docker での実行

```bash
# プロジェクトルートで
docker build -t minirt-parser-test .
docker run --rm minirt-parser-test
```

### ローカル Linux での実行（valgrind が必要）

```bash
make parser_test
./tests/parser/run_leak_tests.sh
```

macOS は valgrind 公式サポート無し → **Docker 推奨**。

### 出力例

```
== 1. accept_files/ — parse succeeds, scene allocated ==
  ✓ 01_minimal.rt (clean)
  ✗ 03_many_objects.rt
       in use at exit: 480 bytes in 12 blocks
       definitely lost: 480 bytes in 12 blocks
  ...

== Summary ==
Total       : 49
Clean       : 36
With leaks  : 13

Files with leaks (full logs preserved):
  - tests/test_files/accept_files/03_many_objects.rt
      log: /tmp/tmp.xxxx
```

### 個別ファイルを調べる

```bash
# コンテナ内で対話的に
docker run --rm -it --entrypoint bash minirt-parser-test
valgrind --leak-check=full ./parser_test tests/test_files/accept_files/01_minimal.rt
```

### parser_test ターゲット

Makefile に `parser_test` ターゲットを追加済み:

```make
PARSER_TEST_SRCS = srcs/main.c \
    srcs/math/vec3_ops.c \
    srcs/math/vec3_len.c \
    srcs/parser/parse*.c \
    srcs/parser/utils*.c

parser_test: $(LIBFT) $(PARSER_TEST_OBJS)
    $(CC) -g $^ -L$(LIBFTDIR) -lft -lm -o parser_test
```

mlx を含まないので X11 環境がない Docker でビルドできます。

### 既知の課題

現状 `main.c` は parse 成功後に `list_clear` を呼ばないので、**accept_files で 12 個以上のオブジェクトを含むシーンは leak が報告されます**。これは parser 自体のバグではなく、main の cleanup 未実装が原因。

修正方針:
```c
/* main.c に追加 */
list_clear((void **)&app.scene.spheres);
list_clear((void **)&app.scene.planes);
list_clear((void **)&app.scene.cylinders);
```

リーク発生時の **parser 内部の問題**（malloc 後 free 漏れ・dispatch エラー時の cleanup 漏れ）を見極めるには:
- 0 件オブジェクトの accept (01_minimal.rt) で leak が出ない → parser 内部は OK、main の問題
- reject ファイルで leak が出る → parser 内部の問題

## 関連

- `docs/0001_rt_parser_accept_reject_cases.md` — フィクスチャー設計の根拠
- `arcchitecture-design/400-interaction-and-errors.md` §8 — エラーポリシー
