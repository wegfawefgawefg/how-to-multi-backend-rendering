# Android + iOS Setup (Scaffold)

This repo now includes CMake presets as a starting point.

## Android (`android-arm64` preset)

Prereqs:
- Android NDK installed.
- `ANDROID_NDK_HOME` set.

Commands:

```bash
cmake --preset android-arm64
cmake --build --preset android-arm64
```

Notes:
- Preset enables `MBR_USE_BUNDLED_SDL=ON` to fetch SDL2 source.
- This is native build scaffolding, not full APK packaging yet.
- Next step is adding a Gradle wrapper project that loads the native lib.

## iOS Simulator (`ios-sim` preset)

Prereqs:
- macOS + Xcode.

Commands:

```bash
cmake --preset ios-sim
cmake --build --preset ios-sim
```

Notes:
- Preset uses `Xcode` generator and simulator sysroot.
- Preset enables `MBR_USE_BUNDLED_SDL=ON`.
- Further app-bundle signing/launch wiring is expected work.

## Why scaffold first?

For educational repos, separating:
- architecture seam design,
- backend implementation,
- platform packaging

keeps complexity manageable and teaches each layer clearly.
