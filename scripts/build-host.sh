#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
"$GBARECOMP_CORE" --bios "$YOSHI_ROOT/roms/gba_bios.bin" --config "$YOSHI_ROOT/sources/gbarecomp/bios/gba_bios.toml" --out "$YOSHI_ROOT/build/generated-bios"
cmake -S "$YOSHI_ROOT/host" -B "$YOSHI_ROOT/build/host" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build "$YOSHI_ROOT/build/host" --target sma3_probe --parallel 4
