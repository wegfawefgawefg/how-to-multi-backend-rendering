# How To Multi-Backend Rendering

Educational C++ repo showing a clean renderer-backend boundary.

Current status:
- Working backend: `sdl2` (SDL window + 2D renderer).
- Demo: opens a window, draws fixed squares, and a circle that follows the mouse.
- Architecture intentionally mirrors larger engines so you can add `opengl`, `vulkan`, `metal`, or `d3d11` later.

## Is it ready for other agents?

Yes. This repo now includes:
- `AGENTS.md` (rules + extension points),
- `CONTRIBUTING.md` (build + backend workflow),
- docs for architecture/patterns/call-stack mapping,
- platform roadmap and pseudocode tutorials.

## Reference Repos (FOSS)

These local repos are used as study references for architecture patterns:
- `../Barony` (thin shim: SDL platform layer + mostly OpenGL renderer path)
- `../OpenTTD` (explicit multi-driver architecture + separate blitter abstraction)
- `../shattered-pixel-dungeon` (libGDX-managed cross-platform backend with game-side wrappers)

See:
- `docs/01-call-stack-maps.md`
- `docs/10-reference-repos.md`

## Quick Start (Desktop)

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
./build/linux-debug/multi_backend_demo
```

If your machine lacks system SDL2, try bundled SDL2:

```bash
cmake -S . -B build/local -DMBR_USE_BUNDLED_SDL=ON
cmake --build build/local
./build/local/multi_backend_demo
```

## Backend Selection

```bash
./build/linux-debug/multi_backend_demo sdl2
```

## Presets

- `linux-debug`
- `linux-release`
- `web-emscripten` (requires `EMSDK` env var)
- `android-arm64` (requires `ANDROID_NDK_HOME`; uses bundled SDL2)
- `ios-sim` (Xcode on macOS; uses bundled SDL2)

## Project Layout

- `include/renderer/IRenderer.hpp`
  backend interface (`init`, `pumpEvents`, `beginFrame`, `draw*`, `endFrame`, `shutdown`)
- `src/renderer/SDLRenderer2D.cpp`
  concrete backend implementation
- `src/renderer/RendererFactory.cpp`
  backend selection
- `src/app/DemoScene.cpp`
  backend-agnostic draw code
- `docs/`
  explainers, tutorials, call-stack maps, pseudocode

## Cross-platform notes

Desktop is fully wired and tested in this repo.
Web/Android/iOS are scaffolded via presets + docs and are the next implementation layer.

See:
- `docs/06-platform-roadmap.md`
- `docs/08-web-emscripten.md`
- `docs/09-android-ios-setup.md`
