#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
cd "$YOSHI_ROOT"
export GBARECOMP_SELFHEAL_RECOMPILE=0
exec "$YOSHI_ROOT/build/host/sma3_probe" --bios "$YOSHI_ROOT/roms/gba_bios.bin" --rom "$YOSHI_ROOT/roms/sma3.gba" --window --save-path "$YOSHI_ROOT/saves/window-test.sav" "$@"
