#!/usr/bin/env bash
# ============================================================================
#   tests/parser/run_leak_tests.sh
#
#   Runs valgrind against every fixture in tests/test_files/ and reports
#   memory leaks per fixture.
#
#   Designed to be executed inside the Dockerfile container (which has
#   valgrind installed). Can also be run on Linux hosts with valgrind.
#
#   Usage:
#       docker run --rm minirt-parser-test
#     or, locally on Linux:
#       make parser_test
#       ./tests/parser/run_leak_tests.sh
# ============================================================================

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROJECT_ROOT"

BINARY="./parser_test"
FIXTURE_DIR="tests/test_files"

# valgrind suppressions / options
VALGRIND_OPTS=(
    "--leak-check=full"
    "--show-leak-kinds=all"
    "--errors-for-leak-kinds=all"
    "--error-exitcode=42"
    "--track-origins=yes"
    "-q"   # quiet on success (suppress banner)
)

# Color codes
if [ -t 1 ]; then
    G='\033[0;32m'; R='\033[0;31m'; Y='\033[0;33m'; B='\033[0;34m'; N='\033[0m'
else
    G=''; R=''; Y=''; B=''; N=''
fi

CLEAN=0
LEAK=0
LEAKED_FILES=()

# ----------------------------------------------------------------------------
# Preflight
# ----------------------------------------------------------------------------

if ! command -v valgrind >/dev/null 2>&1; then
    printf "${R}Error:${N} valgrind not found in PATH.\n"
    printf "Run inside the Docker container: docker run --rm minirt-parser-test\n"
    exit 1
fi

if [ ! -x "$BINARY" ]; then
    printf "${R}Error:${N} %s not found. Run 'make parser_test' first.\n" "$BINARY"
    exit 1
fi

if [ ! -d "$FIXTURE_DIR" ]; then
    printf "${R}Error:${N} fixture dir %s not found.\n" "$FIXTURE_DIR"
    exit 1
fi

# ----------------------------------------------------------------------------
# Helpers
# ----------------------------------------------------------------------------

# Run valgrind against one fixture, print result.
# Returns 0 if no leaks, 1 if leaks detected.
check_leak() {
    local file="$1"
    local label="${2:-$file}"

    local valgrind_log
    valgrind_log=$(mktemp)
    valgrind "${VALGRIND_OPTS[@]}" --log-file="$valgrind_log" \
        "$BINARY" "$file" >/dev/null 2>&1
    local code=$?

    # valgrind exits 42 (our --error-exitcode) if it found leaks.
    # The binary itself might also exit non-zero for reject fixtures — that's OK.
    # We only care about valgrind's leak detection.
    if grep -q "All heap blocks were freed -- no leaks are possible" "$valgrind_log" \
       || [ ! -s "$valgrind_log" ]; then
        printf "${G}  ✓${N} %s (clean)\n" "$label"
        CLEAN=$((CLEAN+1))
        rm -f "$valgrind_log"
        return 0
    fi

    # Extract a brief leak summary
    local def_lost in_use
    def_lost=$(grep -E "definitely lost:" "$valgrind_log" | tail -1 | sed -E 's/^.*definitely lost: //')
    in_use=$(grep -E "in use at exit:" "$valgrind_log" | tail -1 | sed -E 's/^.*in use at exit: //')

    printf "${R}  ✗${N} %s\n" "$label"
    [ -n "$in_use" ]   && printf "       in use at exit: %s\n" "$in_use"
    [ -n "$def_lost" ] && printf "       definitely lost: %s\n" "$def_lost"
    LEAK=$((LEAK+1))
    LEAKED_FILES+=("$file:$valgrind_log")
    return 1
}

print_section() {
    printf "\n${B}== %s ==${N}\n" "$1"
}

# ----------------------------------------------------------------------------
# 1. Accept fixtures
# ----------------------------------------------------------------------------
print_section "1. accept_files/ — parse succeeds, scene allocated"

for f in "$FIXTURE_DIR/accept_files"/*.rt; do
    [ -f "$f" ] || continue
    check_leak "$f" "$(basename "$f")"
done

# ----------------------------------------------------------------------------
# 2. Reject fixtures — per category
# ----------------------------------------------------------------------------

check_reject_category() {
    local dir="$1"
    local title="$2"
    print_section "2. reject_files/$dir — $title"
    if [ ! -d "$FIXTURE_DIR/reject_files/$dir" ]; then
        printf "${Y}  (no fixtures)${N}\n"
        return
    fi
    for f in "$FIXTURE_DIR/reject_files/$dir"/*.rt; do
        [ -f "$f" ] || continue
        check_leak "$f" "$(basename "$f")"
    done
    # non-.rt files (suffix-check tests — usually no malloc, but check anyway)
    for f in "$FIXTURE_DIR/reject_files/$dir"/*.RT \
             "$FIXTURE_DIR/reject_files/$dir"/*.txt \
             "$FIXTURE_DIR/reject_files/$dir"/*.bak; do
        [ -f "$f" ] || continue
        check_leak "$f" "$(basename "$f")"
    done
}

check_reject_category "A_args"       "argument/file errors"
check_reject_category "B_missing"    "missing required elements"
check_reject_category "B_duplicate"  "duplicate elements"
check_reject_category "C_identifier" "unknown identifier"
check_reject_category "C_fields"     "wrong field count"
check_reject_category "D_numeric"    "numeric format"
check_reject_category "E_range"      "out-of-range values"
check_reject_category "F_encoding"   "encoding/structure"

# ----------------------------------------------------------------------------
# Summary
# ----------------------------------------------------------------------------
TOTAL=$((CLEAN + LEAK))
printf "\n${B}== Summary ==${N}\n"
printf "Total       : %d\n" "$TOTAL"
printf "${G}Clean       : %d${N}\n" "$CLEAN"
if [ $LEAK -gt 0 ]; then
    printf "${R}With leaks  : %d${N}\n" "$LEAK"
    printf "\n${R}Files with leaks (full logs preserved):${N}\n"
    for entry in "${LEAKED_FILES[@]}"; do
        local_file="${entry%%:*}"
        local_log="${entry#*:}"
        printf "  - %s\n" "$local_file"
        printf "      log: %s\n" "$local_log"
    done
    printf "\nInvestigate with: cat <log_path>\n"
    exit 1
else
    printf "With leaks  : 0\n"
    printf "\n${G}No memory leaks detected.${N}\n"
    exit 0
fi
