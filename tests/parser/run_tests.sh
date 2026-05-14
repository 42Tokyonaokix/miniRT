#!/usr/bin/env bash
# ============================================================================
#   tests/parser/run_tests.sh
#
#   E2E parser tests. Runs the miniRT binary against every fixture in
#   tests/test_files/ and checks the exit code.
#
#   Conventions:
#     - accept_files/  → exit 0 expected
#     - reject_files/  → non-zero exit expected (plus stderr message)
#
#   Run from project root:
#       make
#       ./tests/parser/run_tests.sh
# ============================================================================

set -u

# Locate project root (parent of "tests")
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROJECT_ROOT"

BINARY="./miniRT"
FIXTURE_DIR="tests/test_files"

# Color codes (disabled if not a TTY)
if [ -t 1 ]; then
    G='\033[0;32m'; R='\033[0;31m'; Y='\033[0;33m'; B='\033[0;34m'; N='\033[0m'
else
    G=''; R=''; Y=''; B=''; N=''
fi

PASS=0
FAIL=0
FAILED=()

# ----------------------------------------------------------------------------
# Helpers
# ----------------------------------------------------------------------------

# Run the binary with a single argument, return its exit code.
run_binary() {
    local arg="$1"
    "$BINARY" "$arg" > /dev/null 2>&1
    return $?
}

# Run the binary with NO arguments (special case).
run_binary_no_arg() {
    "$BINARY" > /dev/null 2>&1
    return $?
}

# Run the binary with TWO arguments (special case).
run_binary_two_args() {
    "$BINARY" "$1" "$2" > /dev/null 2>&1
    return $?
}

# Assert that running with given file results in exit 0 (accept).
assert_accept() {
    local file="$1"
    local label="${2:-$file}"
    run_binary "$file"
    local code=$?
    if [ $code -eq 0 ]; then
        printf "${G}  ✓${N} %s\n" "$label"
        PASS=$((PASS+1))
    else
        printf "${R}  ✗${N} %s (expected exit 0, got %d)\n" "$label" "$code"
        FAIL=$((FAIL+1))
        FAILED+=("$file")
    fi
}

# Assert that running with given file results in non-zero exit (reject).
assert_reject() {
    local file="$1"
    local label="${2:-$file}"
    run_binary "$file"
    local code=$?
    if [ $code -ne 0 ]; then
        printf "${G}  ✓${N} %s (rejected with exit %d)\n" "$label" "$code"
        PASS=$((PASS+1))
    else
        printf "${R}  ✗${N} %s (expected non-zero, got 0)\n" "$label"
        FAIL=$((FAIL+1))
        FAILED+=("$file")
    fi
}

print_section() {
    printf "\n${B}== %s ==${N}\n" "$1"
}

# ----------------------------------------------------------------------------
# Preflight
# ----------------------------------------------------------------------------

if [ ! -x "$BINARY" ]; then
    printf "${R}Error:${N} %s not found or not executable.\n" "$BINARY"
    printf "Run 'make' first.\n"
    exit 1
fi

if [ ! -d "$FIXTURE_DIR" ]; then
    printf "${R}Error:${N} fixture dir %s not found.\n" "$FIXTURE_DIR"
    exit 1
fi

# ----------------------------------------------------------------------------
# 1. CLI argument tests (no fixture file needed)
# ----------------------------------------------------------------------------
print_section "1. CLI argument errors"

# No argument
run_binary_no_arg
if [ $? -ne 0 ]; then
    printf "${G}  ✓${N} No argument is rejected\n"
    PASS=$((PASS+1))
else
    printf "${R}  ✗${N} No argument should be rejected\n"
    FAIL=$((FAIL+1))
    FAILED+=("(no arg)")
fi

# Two arguments
run_binary_two_args "tests/test_files/accept_files/01_minimal.rt" "extra"
if [ $? -ne 0 ]; then
    printf "${G}  ✓${N} Extra argument is rejected\n"
    PASS=$((PASS+1))
else
    printf "${R}  ✗${N} Extra argument should be rejected\n"
    FAIL=$((FAIL+1))
    FAILED+=("(extra arg)")
fi

# Non-existent file (must have .rt suffix to pass the suffix check)
assert_reject "/tmp/does_not_exist_$$.rt" "Non-existent .rt path"

# ----------------------------------------------------------------------------
# 2. Accept tests
# ----------------------------------------------------------------------------
print_section "2. accept_files/ (all should exit 0)"

for f in "$FIXTURE_DIR/accept_files"/*.rt; do
    [ -f "$f" ] || continue
    assert_accept "$f" "$(basename "$f")"
done

# ----------------------------------------------------------------------------
# 3. Reject tests — by category
# ----------------------------------------------------------------------------

reject_category() {
    local dir="$1"
    local title="$2"
    print_section "3. reject_files/$dir — $title"
    if [ ! -d "$FIXTURE_DIR/reject_files/$dir" ]; then
        printf "${Y}  (no fixtures)${N}\n"
        return
    fi
    # *.rt files
    for f in "$FIXTURE_DIR/reject_files/$dir"/*.rt; do
        [ -f "$f" ] || continue
        assert_reject "$f" "$(basename "$f")"
    done
    # Non-.rt files (suffix-check tests)
    for f in "$FIXTURE_DIR/reject_files/$dir"/*.RT \
             "$FIXTURE_DIR/reject_files/$dir"/*.txt \
             "$FIXTURE_DIR/reject_files/$dir"/*.bak; do
        [ -f "$f" ] || continue
        assert_reject "$f" "$(basename "$f")"
    done
}

reject_category "A_args"       "argument/file errors"
reject_category "B_missing"    "missing required elements"
reject_category "B_duplicate"  "duplicate elements"
reject_category "C_identifier" "unknown or wrong identifier"
reject_category "C_fields"     "wrong field count"
reject_category "D_numeric"    "numeric format errors"
reject_category "E_range"      "out-of-range values"
reject_category "F_encoding"   "encoding/structure errors"

# ----------------------------------------------------------------------------
# Summary
# ----------------------------------------------------------------------------
TOTAL=$((PASS + FAIL))
printf "\n${B}== Summary ==${N}\n"
printf "Total : %d\n" "$TOTAL"
printf "${G}Pass  : %d${N}\n" "$PASS"
if [ $FAIL -gt 0 ]; then
    printf "${R}Fail  : %d${N}\n" "$FAIL"
    printf "\n${R}Failed tests:${N}\n"
    for f in "${FAILED[@]}"; do
        printf "  - %s\n" "$f"
    done
    exit 1
else
    printf "Fail  : 0\n"
    printf "\n${G}All tests passed.${N}\n"
    exit 0
fi
