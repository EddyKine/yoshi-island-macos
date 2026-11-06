#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
cd "$YOSHI_ROOT"
mkdir -p saves menu-profile
export GBARECOMP_SELFHEAL_RECOMPILE=0
exec "$YOSHI_ROOT/build/menu/sma3_menu" --bios "$YOSHI_ROOT/roms/gba_bios.bin" --rom "$YOSHI_ROOT/roms/sma3.gba" --window --save-path "$YOSHI_ROOT/saves/public.sav" "$@"
