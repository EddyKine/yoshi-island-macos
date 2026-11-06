#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
python3 "$YOSHI_ROOT/scripts/validate_rom.py" "$YOSHI_ROOT/roms/sma3.gba"
python3 - "$YOSHI_ROOT/roms/gba_bios.bin" <<'PYBIOS'
from pathlib import Path
import hashlib, sys
b = Path(sys.argv[1]).read_bytes()
if len(b) != 16384 or hashlib.sha1(b).hexdigest() != '300c20df6731a33952ded8c436f7f186d25d3492':
    raise SystemExit('BIOS incompatible: se requieren 16384 bytes y el SHA1 documentado')
PYBIOS
cmake -S "$YOSHI_ROOT/sources/gbarecomp" -B "$YOSHI_ROOT/build/framework" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64 -DGBARECOMP_COMPILER_CACHE=OFF
cmake --build "$YOSHI_ROOT/build/framework" --target gba_recompile --parallel 4
bash "$YOSHI_ROOT/scripts/generate-and-build.sh"
bash "$YOSHI_ROOT/scripts/build-host.sh"
bash "$YOSHI_ROOT/scripts/build-menu.sh"
