# Tutorial: From Single Renderer to Multi-Backend

## Goal

Take a direct-render app and migrate it into:
- backend-agnostic app logic,
- backend-specific implementation classes,
- factory-based backend selection.

## Step 1: Define the seam

Create `IRenderer` with only what app logic needs right now:
- frame lifecycle (`beginFrame/endFrame`),
- input polling (`pumpEvents`),
- minimum draw primitives (`drawFilledRect/drawFilledCircle`).

Do not overdesign. Expand interface only when needed.

## Step 2: Move draw calls behind interface

Before:
- app calls SDL/GL functions directly.

After:
- app calls `renderer.draw*()` only.

This repo does this in `src/app/DemoScene.cpp`.

## Step 3: Implement one concrete backend well

`SDLRenderer2D` is the first backend:
- init window + renderer,
- process events,
- draw primitives,
- present.

The first backend validates your interface. If implementing it feels awkward, adjust interface.

## Step 4: Add a factory

`RendererFactory` resolves backend name to implementation instance.
This gives you runtime backend selection and isolates creation logic.

## Step 5: Add capabilities (optional)

When you add richer backends, add capability queries:
- `supportsInstancing`,
- `supportsCompute`,
- `supportsMSAA`.

Keep your app behavior deterministic when capability is missing (fallback path).

## Step 6: Add second backend

Once backend #2 is added:
- compare behavior with same scene,
- keep API contract stable,
- avoid backend-specific leaks into app code.

