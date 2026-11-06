#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
python3 "$YOSHI_ROOT/scripts/validate_rom.py" "$YOSHI_ROOT/roms/sma3.gba"
if [ ! -f "$YOSHI_ROOT/build/sma3-generated/CMakeLists.txt" ]; then
 python3 "$YOSHI_ROOT/sources/gbarecomp/tools/cli.py" build --rom "$YOSHI_ROOT/roms/sma3.gba" --output "$YOSHI_ROOT/build/sma3-generated" --codegen-shards 16
fi
cmake -S "$YOSHI_ROOT/build/sma3-generated" -B "$YOSHI_ROOT/build/cartridge" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build "$YOSHI_ROOT/build/cartridge" --parallel 2
