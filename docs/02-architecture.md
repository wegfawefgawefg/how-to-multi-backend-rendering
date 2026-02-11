# Architecture In This Repo

## Data flow

1. `main.cpp` selects a backend with `RendererFactory`.
2. Backend is created as `std::unique_ptr<IRenderer>`.
3. Demo scene renders only through `IRenderer` methods.
4. Backend implementation translates those calls to API-specific calls.

## Why this seam is useful

`IRenderer` is your contract. If it stays stable:
- app logic does not care if backend is SDL/OpenGL/Vulkan/etc.
- swapping backends does not require rewriting gameplay/render call sites.
- tests/mocks become easier (you can fake a renderer).

## Tradeoff

A stricter interface means less backend-specific power available directly.
That is good for educational projects and portability, but large engines often add:
- low-level escape hatches,
- feature flags/capability queries,
- command buffer style APIs.
