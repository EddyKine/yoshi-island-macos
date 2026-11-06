# macOS v0.1.0-beta

Descarga: https://github.com/EddyKine/yoshi-island-macos/releases/tag/v0.1.0-beta

ZIP con **Yoshi Island.app**, SDL incluido y LEEME.txt. Requiere Apple Silicon y macOS 27.0 o posterior. Pruebas actuales en macOS 27.2; el motor tenía validación previa en macOS 27.0.1. No hay pruebas en un segundo Mac físico ni en Intel.

En el primer inicio se selecciona una ROM propia compatible y una BIOS GBA propia. Se valida el hash y se recuerda la ruta. Los archivos permanecen fuera del bundle. Option al iniciar permite elegir otros archivos. No se importan partidas ni preferencias privadas.

Datos nuevos en `~/Library/Application Support/EddyKine/Yoshi Island`; partida en `saves/game.sav`. Las apps y partidas locales anteriores permanecen independientes.

## Paquete y comprobaciones

- ZIP generado desde una lista explícita de archivos públicos; sin ROM, BIOS, partidas, perfiles, capturas ni metadatos AppleDouble.
- Sin una copia cruda de la ROM o BIOS dentro de ningún archivo del bundle, comprobado contra las imágenes locales completas.
- Extracción con ditto en otra carpeta, permisos ejecutables y firma ad hoc profunda/estricta válidos.
- Dependencias de carga libres de rutas Homebrew. Las librerías SDL incluidas se observaron cargadas en la copia trasladada.
- Rechazo de ROM ausente, ejecución de 600 fotogramas y segundo inicio de 30 fotogramas con rutas recordadas y datos desechables.
- Selector nativo de ROM observado; transición al selector de BIOS observada después de seleccionar una ROM compatible.
- El runtime del juego se conserva; los cambios de esta release corresponden al lanzador y al empaquetado.

SHA256 del ZIP:

```text
d8ec33a8acedc5e55d19c0eeb9d94c464276073d2b1e60b30a2a3905c3fda867  Yoshi-Island-v0.1.0-beta-macOS-arm64.zip
```

Firma ad hoc: sin Developer ID ni notarización. Gatekeeper puede bloquear la apertura en otro Mac. No se garantiza apertura sin avisos. Beta con cobertura parcial de gameplay. Sigue usando código recompilado con fallback al intérprete.

## Reproducir el paquete

Después de compilar el proyecto, ejecuta:

```sh
python3 scripts/package-release.py --output build/releases/mi-beta
```

El directorio de salida debe ser nuevo. `verify-release.py`, en la misma carpeta del script, permite verificar el ZIP usando `--archive`, `--rom` y `--bios`. Las pruebas usan un directorio nuevo bajo build/.
