# Platform Roadmap (macOS / Windows / Linux / Android)

## Current

- C++ + CMake
- SDL2 backend works on desktop targets (macOS/Windows/Linux).

## Android options

## Option A (recommended for this repo): SDL2 Android build path

- Keep C++ core + backend interface.
- Build with SDL's Android Gradle project and call into your C++ app.
- Keep the same `IRenderer` and add an `sdl2-android` target config.

Pros:
- same codebase style as desktop.
- minimal architectural churn.

Cons:
- Android native build setup is more involved than desktop.

## Option B: Engine/framework delegation

Use a framework like libGDX/Unity/Godot for platform abstraction.

Pros:
- faster Android/iOS shipping.

Cons:
- less control over low-level renderer architecture.

## Suggested next implementation plan

1. Add `CMakePresets.json` for Linux/macOS/Windows presets.
2. Add `opengl` backend on desktop to illustrate multi-backend in pure C++.
3. Add SDL Android project wiring while keeping `src/app` untouched.

