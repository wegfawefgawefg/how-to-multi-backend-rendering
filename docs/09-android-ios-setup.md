# Android + iOS Setup

## Android from Linux

This repo supports Android native and APK builds on Linux.

### What is included

- Android CMake preset: `android-arm64`
- Android Gradle app scaffold under `android/`
- SDL Android Java glue (`org.libsdl.app`) vendored from SDL2 release `2.30.9`
- App activity: `com.example.multibackend.DemoActivity`

### Linux prerequisites

- Android SDK (platform-tools + platforms)
- Android NDK
- Java 17
- Gradle (or Android Studio, which bundles Gradle integration)
- `ANDROID_NDK_HOME` set
- `ANDROID_SDK_ROOT` set (recommended)

### 1. Build native code with CMake preset

```bash
export ANDROID_NDK_HOME=/path/to/android-ndk
cmake --preset android-arm64
cmake --build --preset android-arm64
```

### 2. Build APK with Gradle

```bash
cd android
gradle assembleDebug
```

APK output:
- `android/app/build/outputs/apk/debug/app-debug.apk`

### 3. Run on emulator (Linux)

Install Android command line components if needed:

```bash
sdkmanager "platform-tools" "platforms;android-34" "system-images;android-34;google_apis;x86_64" "emulator" "build-tools;34.0.0"
```

Create and start an emulator:

```bash
avdmanager create avd -n mbr-api34 -k "system-images;android-34;google_apis;x86_64"
emulator -avd mbr-api34
```

Install and launch:

```bash
adb install -r app/build/outputs/apk/debug/app-debug.apk
adb shell am start -n com.example.multibackend/com.example.multibackend.DemoActivity
```

### Scripted workflow (recommended)

From repo root:

```bash
scripts/android/setup_sdk.sh
scripts/android/create_avd.sh
scripts/android/start_emulator.sh
scripts/android/build_native.sh
scripts/android/build_apk.sh
scripts/android/install_apk.sh
scripts/android/run_app.sh
```

During development:

```bash
scripts/android/dev_cycle.sh
```

Logs:

```bash
scripts/android/logcat.sh
```

Environment defaults are in `scripts/android/env.sh` (`ANDROID_SDK_ROOT`, `ANDROID_NDK_HOME`, API level, AVD name).

### Notes

- Emulators are a normal workflow for SDL Android development.
- For better performance/input validation, also test on a physical device.

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
- iOS app packaging/signing/launch still requires macOS/Xcode workflows.
