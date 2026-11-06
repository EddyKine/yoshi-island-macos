#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
cmake -S "$YOSHI_ROOT/host-menu" -B "$YOSHI_ROOT/build/menu" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build "$YOSHI_ROOT/build/menu" --target sma3_menu sma3_controls_tests sma3_menu_host_tests --parallel 4
ctest --test-dir "$YOSHI_ROOT/build/menu" -R '^sma3_' --output-on-failure
