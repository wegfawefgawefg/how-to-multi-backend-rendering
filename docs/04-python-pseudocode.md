# Python-Style Pseudocode

## Backend interface shape

```python
class Renderer:
    def init(self, title: str, width: int, height: int) -> bool: ...
    def pump_events(self, input_state): ...
    def begin_frame(self, clear_color): ...
    def draw_rect(self, rect, color): ...
    def draw_circle(self, center, radius, color): ...
    def end_frame(self): ...
    def shutdown(self): ...
```

## Factory

```python
def create_renderer(name: str) -> Renderer | None:
    name = name.lower()
    if name in ("", "sdl2", "sdl"):
        return SDLRenderer2D()
    if name == "opengl":
        return OpenGLRenderer()  # future
    if name == "vulkan":
        return VulkanRenderer()  # future
    return None
```

## App loop

```python
renderer = create_renderer(config.backend)
renderer.init("Demo", 960, 600)

while not input_state.quit:
    renderer.pump_events(input_state)

    renderer.begin_frame(clear=(22, 24, 28, 255))
    renderer.draw_rect((80, 80, 90, 90), (255, 99, 71, 255))
    renderer.draw_rect((220, 120, 120, 80), (255, 215, 0, 255))
    renderer.draw_circle((input_state.mouse_x, input_state.mouse_y), 26, (80, 255, 140, 220))
    renderer.end_frame()

renderer.shutdown()
```

## Capability-aware variant

```python
if renderer.supports("instancing"):
    renderer.draw_instanced(...)
else:
    for item in items:
        renderer.draw(...)
```
