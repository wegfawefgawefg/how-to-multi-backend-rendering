#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
"$ROOT/scripts/android/build_native.sh"
"$ROOT/scripts/android/build_apk.sh"
"$ROOT/scripts/android/install_apk.sh"
"$ROOT/scripts/android/run_app.sh"
