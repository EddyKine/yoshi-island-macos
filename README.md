# Yoshi’s Island / SMA3 para macOS Apple Silicon

Integración experimental de **Super Mario Advance 3: Yoshi’s Island** para Mac arm64, basada en [GBARecomp](https://github.com/mstan/gbarecomp), con menú durante el juego, ajustes de pantalla/audio y reasignación del mando mediante [recomp-ui](https://github.com/RetroPortingToolKit/recomp-ui).

**Debes aportar tu propia ROM y BIOS compatibles.** Este repositorio contiene fuentes, parches y referencias a dependencias; no distribuye el juego, la BIOS, código generado a partir de ellos, partidas ni una app compilada.

## Estado

El usuario aprobó manualmente el juego y la variante con ajustes el 27 de octubre de 2026, con buena jugabilidad y música, sin errores gráficos observados durante su sesión. No se ha validado todo el juego. Se ejecuta código recompilado con fallback al intérprete; no es recompilación estática completa.

Se conserva la versión local aprobada. La publicación no sustituye sus ejecutables ni modifica las partidas. Antes de publicar se repitieron las pruebas del menú, controles, audio del framework, PPU y generación de código; ver `docs/PUBLICACION.md`.

## Requisitos

- Mac Apple Silicon; probado localmente en macOS 27. No se certifican otras versiones.
- Xcode Command Line Tools, Git, CMake, Ninja, Python 3 y SDL2. El proyecto usa la instalación Homebrew arm64 en `/opt/homebrew`.
- Espacio para compilar: la generación local produce aproximadamente 462 MiB de fuentes, más objetos y bibliotecas.
- ROM USA revisión 0, código A3AE, 4.194.304 bytes, SHA1 `7352d2bd064d9ebaec579e264228aa21c7345b80`.
- BIOS de 16.384 bytes, SHA1 `300c20df6731a33952ded8c436f7f186d25d3492`.

## Compilar

```sh
git clone https://github.com/EddyKine/yoshi-island-macos.git
cd yoshi-island-macos
brew install cmake ninja python sdl2
mkdir -p roms
# Coloca tu ROM en roms/sma3.gba y tu BIOS en roms/gba_bios.bin.
bash scripts/setup-sources.sh
bash scripts/build-all.sh
bash scripts/run-menu.sh
```

La preparación obtiene dependencias fijadas y aplica el parche local de GBARecomp. Solo inicializa los submódulos externos necesarios para este objetivo de escritorio. La compilación genera el cartucho y la BIOS localmente, compila el host base y el host con menú, y ejecuta las pruebas del menú.

Los binarios quedan en `build/host/sma3_probe` y `build/menu/sma3_menu`. No se genera un bundle público listo para descargar. Los lanzadores `.app` privados del desarrollo original no se publican porque dependen de rutas locales y algunos paquetes contienen ROM/BIOS.

## Jugar y configurar

`bash scripts/run-menu.sh` usa `saves/public.sav`, independiente de las partidas locales anteriores. Las preferencias se guardan en `menu-profile/`, excluido de Git.

- Abrir/cerrar menú: **Esc** o **Back + Start** del mando; Guide también funciona si macOS lo entrega.
- Navegar: cruceta/flechas; A/Enter confirma; B retrocede.
- Controles: seleccionar una acción GBA, soltar botones y pulsar el botón físico nuevo. Los duplicados intercambian asignaciones. Esc/Guide cancela la captura.
- Teclado: flechas, X = A, Z = B, C = L, V = R, Enter = Start, Shift derecho = Select.
- Imagen interna de 240×160, proporción 3:2; escala, pantalla completa, filtro y volumen desde el menú.

## Créditos y límites

Ver [NOTICE.md](NOTICE.md) y [LICENSE](LICENSE). GBARecomp usa PolyForm Noncommercial 1.0.0; recomp-ui y otras dependencias conservan sus términos. Mantén sus avisos al redistribuir.

La fidelidad de todas las escenas, estabilidad de una partida completa y compatibilidad con otros Mac o mandos siguen pendientes. La aprobación manual cubre la sesión observada y no equivale a una certificación de todo el juego.
