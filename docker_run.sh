#!/bin/bash
# Run miniRT inside Docker with X11 forwarding to XQuartz on macOS.
#
# Prerequisites (one-time setup):
#   1. brew install --cask xquartz
#   2. Open XQuartz > Preferences > Security > check "Allow connections from network clients"
#   3. Log out and back in (or reboot)
#
# Usage: ./docker_run.sh [scene_file]
#   e.g. ./docker_run.sh tests/test_files/test.rt

set -e

SCENE="${1:-tests/test_files/accept_files/01_minimal.rt}"
IMAGE="minirt-dev"

# ── 1. Verify XQuartz is running ──────────────────────────────────────────────
if ! pgrep -x "X11.bin" > /dev/null 2>&1 && ! pgrep -x "Xquartz" > /dev/null 2>&1; then
    echo "[INFO] Starting XQuartz..."
    open -a XQuartz
    sleep 3
fi

# ── 2. Allow Docker containers to connect to XQuartz ─────────────────────────
xhost + 127.0.0.1 > /dev/null 2>&1 || true

# ── 3. Build image if it doesn't exist ───────────────────────────────────────
if ! docker image inspect "$IMAGE" > /dev/null 2>&1; then
    echo "[INFO] Building Docker image..."
    docker build -t "$IMAGE" -f Dockerfile .
fi

# ── 4. Run container ──────────────────────────────────────────────────────────
SCENE_ARG="$SCENE"

docker run --rm -it \
    -e DISPLAY=host.docker.internal:0 \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v "$(pwd)":/miniRT \
    -w /miniRT\
    "$IMAGE" \
    bash -c "make re && ./miniRT $SCENE_ARG"
