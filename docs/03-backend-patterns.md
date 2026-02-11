# Common Multi-Backend Patterns

## Pattern A: Thin wrappers (small projects)

- One primary backend.
- Minimal abstraction.
- Low complexity, fast iteration.

## Pattern B: Interface + factories (mid-size engines)

- `IRenderer` + concrete backend classes.
- Backend selected at startup/config.
- Good balance for educational and indie engine codebases.

## Pattern C: RHI / Render Graph (large engines)

- API-neutral command recording.
- Backend-specific command translation layers.
- High upfront complexity, high long-term scalability.

## What this repo uses

Pattern B.

Reason:
- Matches your current goal (learn architecture seams).
- Easy to grow into Pattern C later.
