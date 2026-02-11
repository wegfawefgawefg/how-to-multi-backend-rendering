# Reference Repos

These FOSS repos are used as architectural references while evolving this educational project.

## Local Paths

- `/home/vega/Coding/Training/Barony`
- `/home/vega/Coding/Training/OpenTTD`
- `/home/vega/Coding/Training/shattered-pixel-dungeon`

## Why each one matters

## Barony

- Good example of a thin rendering shim.
- SDL handles platform/window/context concerns.
- Most render work is a single API path (OpenGL-focused).

Use it to learn:
- how simple abstractions look in real production code,
- why thin shims are easy to ship but harder to multi-backend later.

## OpenTTD

- Strong explicit abstraction boundaries.
- Distinct video drivers and blitters with factory selection.
- Multiple backend implementations are first-class citizens.

Use it to learn:
- plugin/factory architecture,
- how to separate pixel pipeline decisions from platform/video output.

## Shattered Pixel Dungeon

- Cross-platform via libGDX backend delegation.
- Game logic stays mostly backend-agnostic through wrapper layers.
- Practical mobile/desktop shipping model.

Use it to learn:
- delegated abstraction (engine/framework does backend heavy lifting),
- tradeoff between control and delivery speed.

## How this repo uses those lessons

- Keep app logic backend-agnostic (`src/app/*`).
- Keep API-specific code in renderer implementations (`src/renderer/*`).
- Keep backend selection explicit and centralized (`RendererFactory`).

For direct call-flow comparison, see `docs/01-call-stack-maps.md`.
