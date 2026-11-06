#!/bin/bash
set -euo pipefail
source "$(dirname "$0")/env.sh"
cd "$YOSHI_ROOT"
git submodule update --init -- sources/gbarecomp sources/recomp-ui
git -C sources/gbarecomp submodule update --init -- external/arm-recomp-core external/recomp-net external/rbengine
patch_file="$YOSHI_ROOT/patches/gbarecomp-sma3.patch"
if git -C sources/gbarecomp apply --reverse --check "$patch_file" 2>/dev/null; then
  echo "SMA3 patch already applied"
else
  git -C sources/gbarecomp apply --check "$patch_file"
  git -C sources/gbarecomp apply "$patch_file"
fi
