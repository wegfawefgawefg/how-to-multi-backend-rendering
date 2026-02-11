# Web Build (Emscripten)

This project includes a `web-emscripten` CMake preset.

## Prereqs

- Emscripten SDK installed.
- `EMSDK` environment variable set.

Example:

```bash
source /path/to/emsdk/emsdk_env.sh
echo $EMSDK
```

## Configure + build

```bash
cmake --preset web-emscripten
cmake --build --preset web-emscripten
```

Expected output:
- `build/web-emscripten/multi_backend_demo.html`
- associated `.js` and `.wasm`

## Run locally

Use any static file server from build dir.

```bash
cd build/web-emscripten
python3 -m http.server 8080
```

Open `http://localhost:8080/multi_backend_demo.html`.

## Notes

- CMake enables `-sUSE_SDL=2` for Emscripten builds.
- Current demo uses mouse input + basic 2D primitives.
