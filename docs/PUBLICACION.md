# Preparación pública — 6 de noviembre de 2026

Repositorio: https://github.com/EddyKine/yoshi-island-macos . Rama: `main`.

## Contenido

Se publican los hosts base y con menú, sus controles/pruebas, scripts de generación y compilación, documentación, el parche del framework y submódulos fijados de GBARecomp y recomp-ui. No se publica el paquete portable privado, la ROM, la BIOS, fuentes generadas, partidas, configuraciones personales ni capturas de diagnóstico.

El parche incluye la limpieza de retornos tras IRQ y su regresión, más la integración condicional del menú, persistencia de ajustes y reasignación de controles. Las dependencias conservan sus licencias y revisiones originales. Ver `NOTICE.md`.

## Verificado al preparar la publicación

- Menú y controles: 2/2 pruebas CTest aprobadas (`sma3_controls`, `sma3_menu_host`).
- Framework: `audio_playback_tests`, `ppu_smoke_tests`, `codegen_tests`, 3/3 aprobadas.
- Regresión `build/host/framework/tail_dispatch_tests`: aprobada.
- El parche se aplica a una extracción limpia del commit fijado de GBARecomp; comprobación inversa también aprobada sobre las fuentes locales.
- Sintaxis Bash de scripts de preparación, generación, build y ejecución: aprobada.
- ROM y BIOS locales verificadas por hash; solo se usan para la prueba local, no se publican.
- Host con menú: 600 fotogramas sin ventana, salida 0, con partida desechable bajo `build/publication-*/`.
- Auditoría del índice Git: solo archivos nombrados, submódulos y parche; sin archivos privados o generados.

Estas pruebas reutilizan la compilación local existente. No equivalen a una compilación completa en un segundo Mac o a completar todos los niveles. El parche se verificó contra fuentes limpias, pero aún no se ha compilado todo el repositorio público en otra máquina. Se conserva el fallback al intérprete y la validación manual anterior no certifica todo el juego.

Los ejecutables aprobados, bundles privados y partidas anteriores se preservan. No se crea una release binaria pública en esta publicación de fuentes.
