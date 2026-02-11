# Call-Stack Maps (Barony vs OpenTTD vs Shattered Pixel Dungeon)

## Barony (thin shim)

`game code -> drawImage()/drawRect() helpers -> OpenGL calls -> SDL_GL_SwapWindow`

Characteristics:
- SDL mostly for platform/window/input.
- Rendering path is effectively one backend (OpenGL).
- Abstraction exists, but not a true multi-backend renderer.

## OpenTTD (true driver + blitter split)

`game UI/world draw -> blitter (sprite compose) -> video driver backend -> present`

Characteristics:
- `VideoDriver` interface with multiple backends (`sdl`, `sdl-opengl`, `win32`, etc.).
- Separate `BlitterFactory` abstraction for pixel/sprite pipeline.
- Strong plugin/factory architecture.

## Shattered Pixel Dungeon (engine delegated to libGDX)

`game scene code -> noosa/glwrap wrappers -> libGDX backend -> platform graphics API`

Characteristics:
- Core game code stays mostly backend-agnostic.
- Desktop/Android/iOS launchers choose libGDX backend.
- iOS uses MetalANGLE (Metal-backed GL compatibility path).

## Takeaway

- Thin shim: fastest to ship.
- Explicit driver interfaces: best for long-term engine control.
- External engine abstraction (libGDX/Unity/etc.): fastest cross-platform reach.
