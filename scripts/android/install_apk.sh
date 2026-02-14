#!/usr/bin/env bash
set -euo pipefail
source "$(dirname "$0")/env.sh"

require_cmd adb
APK="$ANDROID_DIR/app/build/outputs/apk/debug/app-debug.apk"

if [[ ! -f "$APK" ]]; then
    echo "APK not found: $APK" >&2
    echo "Run scripts/android/build_apk.sh first." >&2
    exit 1
fi

adb install -r "$APK"
