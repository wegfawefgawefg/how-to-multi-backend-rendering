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

## Build + Run By Target

### Linux (Debian/Ubuntu/Arch, etc.)

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
./build/linux-debug/multi_backend_demo
```

If your machine lacks system SDL2, use bundled SDL2:

```bash
cmake -S . -B build/local -DMBR_USE_BUNDLED_SDL=ON
cmake --build build/local
./build/local/multi_backend_demo
```

### macOS

```bash
cmake -S . -B build/macos-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/macos-debug
./build/macos-debug/multi_backend_demo
```

If SDL2 is not installed system-wide on macOS:

```bash
cmake -S . -B build/macos-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DMBR_USE_BUNDLED_SDL=ON
cmake --build build/macos-debug
./build/macos-debug/multi_backend_demo
```

### Windows (PowerShell + Visual Studio Build Tools)

```powershell
cmake -S . -B build/windows-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DMBR_USE_BUNDLED_SDL=ON
cmake --build build/windows-debug
.\build\windows-debug\multi_backend_demo.exe
```

### Web (Emscripten)

```bash
source /path/to/emsdk/emsdk_env.sh
cmake --preset web-emscripten
cmake --build --preset web-emscripten
cd build/web-emscripten
python3 -m http.server 8080
```

Open `http://localhost:8080/multi_backend_demo.html`.

### Android (Linux build + emulator)

```bash
export ANDROID_NDK_HOME=/path/to/android-ndk
cmake --preset android-arm64
cmake --build --preset android-arm64
```

To build an APK from Linux:

```bash
cd android
gradle assembleDebug
```

Install and launch on device/emulator:

```bash
adb install -r app/build/outputs/apk/debug/app-debug.apk
adb shell am start -n com.example.multibackend/com.example.multibackend.DemoActivity
```

Android emulator setup/run commands are documented in `docs/09-android-ios-setup.md`.

Shortcut scripts:

```bash
scripts/android/setup_sdk.sh       # one-time SDK/NDK/emulator packages
scripts/android/create_avd.sh      # one-time AVD create
scripts/android/start_emulator.sh  # boot emulator + wait for adb
scripts/android/build_native.sh    # cmake android-arm64 build
scripts/android/build_apk.sh       # ./gradlew assembleDebug
scripts/android/install_apk.sh     # adb install
scripts/android/run_app.sh         # adb launch activity
scripts/android/dev_cycle.sh       # build native + apk + install + run
scripts/android/logcat.sh          # filtered runtime logs
```

### iOS Simulator (scaffold)

```bash
cmake --preset ios-sim
cmake --build --preset ios-sim
```

This currently validates CMake/Xcode project generation and native build. App bundle/signing/launch wiring is tracked in `docs/09-android-ios-setup.md`.

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
