#!/usr/bin/env bash
set -euo pipefail
source "$(dirname "$0")/env.sh"

cd "$ANDROID_DIR"
./gradlew assembleDebug
