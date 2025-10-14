#!/usr/bin/env bash
# run_tests.sh — build libft, copy libft.a, build & run tests
# Usage: ./run_tests.sh [--bonus|-b] [group1 group2 ...]

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TARGET_ROOT="$(realpath "$SCRIPT_DIR/..")"  # parent is libft repo

if [ ! -f "$TARGET_ROOT/Makefile" ]; then
  echo "Error: Cannot find Makefile in $TARGET_ROOT"
  exit 1
fi

# parse args: optional --bonus/-b before test group names
INCLUDE_BONUS=0
ARGS=()
while [ "$#" -gt 0 ]; do
  case "$1" in
    --bonus|-b)
      INCLUDE_BONUS=1
      shift
      ;;
    *)
      ARGS+=("$1")
      shift
      ;;
  esac
done

echo "Building target's libft..."
if [ "$INCLUDE_BONUS" -eq 1 ]; then
  ( cd "$TARGET_ROOT" && make -s fclean >/dev/null 2>&1 || true && make -s bonus ) || {
      echo "Makefile failed to build (bonus)"
      exit 2
  }
else
  ( cd "$TARGET_ROOT" && make -s fclean >/dev/null 2>&1 || true && make -s ) || {
      echo "Makefile failed to build"
      exit 2
  }
fi

if [ ! -f "$TARGET_ROOT/libft.a" ]; then
  echo "Error: libft.a not found after build"
  exit 3
fi

# copy libft.a into tester folder
cp "$TARGET_ROOT/libft.a" "$SCRIPT_DIR/libft.a"

# build tests (pass TEST_BONUS=1 to enable bonus test registration/build)
echo "Compiling libft_tests..."
if [ "$INCLUDE_BONUS" -eq 1 ]; then
  # run fclean in tester (ignore failure), then copy libft.a, then build with bonus
  ( cd "$SCRIPT_DIR" && make -s fclean >/dev/null 2>&1 || true )
  cp "$TARGET_ROOT/libft.a" "$SCRIPT_DIR/libft.a"
  ( cd "$SCRIPT_DIR" && make -s TEST_BONUS=1 ) || {
      echo "Failed to build tests (bonus)"
      exit 4
  }
else
  ( cd "$SCRIPT_DIR" && make -s fclean >/dev/null 2>&1 || true )
  cp "$TARGET_ROOT/libft.a" "$SCRIPT_DIR/libft.a"
  ( cd "$SCRIPT_DIR" && make -s ) || {
      echo "Failed to build tests"
      exit 4
  }
fi

# run tests (pass groups optionally)
BINARY="$SCRIPT_DIR/libft_tests"

if [ ! -x "$BINARY" ]; then
    echo "Error: test binary not found or not executable: $BINARY"
    exit 5
fi

if [ "${#ARGS[@]}" -gt 0 ]; then
    "$BINARY" "${ARGS[@]}"
else
    "$BINARY"
fi
