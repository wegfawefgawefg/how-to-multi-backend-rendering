# Contributing

## Build

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
./build/linux-debug/multi_backend_demo
```

## Coding conventions
- C++17.
- Keep headers minimal and focused.
- Prefer explicit names over shorthand.
- Backend code must not leak into app layer.

## Adding a new renderer backend
1. Implement `IRenderer` in a new class (e.g. `OpenGLRenderer2D`).
2. Register backend name in `RendererFactory`.
3. Update `README.md` and docs.
4. Add at least one platform note in `docs/` if setup differs.

## Commit expectations
- Small, scoped commits are preferred.
- Include docs changes with architecture/code changes.
