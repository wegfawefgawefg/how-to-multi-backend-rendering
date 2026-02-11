# AGENTS.md

Purpose: make this repo easy for multiple agents/humans to extend without breaking architecture.

## Project intent
- Educational multi-backend rendering reference.
- Keep app logic backend-agnostic.
- Add backends incrementally with clear tradeoffs.

## Ground rules
1. Do not call SDL/OpenGL/etc directly from `src/app/*`.
2. Add backend-specific code only under `src/renderer/*` and `include/renderer/*`.
3. If a new app feature needs rendering, add it to `IRenderer` first, then implement per backend.
4. Keep docs updated for every architectural change.

## Main extension points
- `include/renderer/IRenderer.hpp`: backend contract.
- `src/renderer/RendererFactory.cpp`: backend selection.
- `src/renderer/*`: concrete backend implementations.
- `src/app/*`: backend-agnostic scene logic.

## Required checks before finalizing changes
- `cmake --preset linux-debug`
- `cmake --build --preset linux-debug`
- Verify demo starts and renders if environment supports display.

## Docs to update when adding a backend
- `README.md`
- `docs/02-architecture.md`
- `docs/03-backend-patterns.md`
- Add a new backend-specific doc under `docs/`

## Non-goals (for now)
- Full production engine framework.
- ECS, physics, asset pipeline complexity.
- Advanced render graph.

## Reference checklist (required in backend PRs)
For any PR that adds/changes backend architecture, include a short section in the PR description:

1. `Reference pattern used:`
   - `Barony` (thin shim), or
   - `OpenTTD` (explicit driver/factory split), or
   - `Shattered Pixel Dungeon` (delegated backend abstraction)
2. `Why this pattern fits this change:` 1-3 sentences.
3. `Boundary check:` confirm app code in `src/app/*` stayed backend-agnostic.
4. `Docs updated:` list files changed under `docs/` and `README.md` (if applicable).

If no reference applies, state `none` and explain why in 1-2 sentences.
