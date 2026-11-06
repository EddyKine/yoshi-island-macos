# Ejecutar con: source scripts/env.sh, desde cualquier directorio.
YOSHI_ROOT="$(cd "$(dirname "${BASH_SOURCE:-$0}")/.." && pwd)"
export TMPDIR="$YOSHI_ROOT/tmp" TMP="$YOSHI_ROOT/tmp" TEMP="$YOSHI_ROOT/tmp"
export XDG_CACHE_HOME="$YOSHI_ROOT/cache" PYTHONPYCACHEPREFIX="$YOSHI_ROOT/cache/python"
export CLANG_MODULE_CACHE_PATH="$YOSHI_ROOT/cache/clang"
export GBARECOMP_CORE="$YOSHI_ROOT/build/framework/gba_recompile"

mkdir -p "$YOSHI_ROOT/tmp" "$YOSHI_ROOT/cache/clang" "$YOSHI_ROOT/logs" "$YOSHI_ROOT/saves"
