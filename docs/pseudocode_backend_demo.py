"""
Educational pseudocode only.
Shows a backend-agnostic render loop using a renderer interface.
"""

from dataclasses import dataclass


@dataclass
class Color:
    r: int
    g: int
    b: int
    a: int = 255


@dataclass
class Rect:
    x: int
    y: int
    w: int
    h: int


@dataclass
class InputState:
    quit_requested: bool = False
    mouse_x: int = 0
    mouse_y: int = 0


class Renderer:
    def init(self, title: str, width: int, height: int) -> bool: ...
    def pump_events(self, input_state: InputState) -> None: ...
    def begin_frame(self, clear: Color) -> None: ...
    def draw_filled_rect(self, rect: Rect, color: Color) -> None: ...
    def draw_filled_circle(self, x: int, y: int, radius: int, color: Color) -> None: ...
    def end_frame(self) -> None: ...
    def shutdown(self) -> None: ...


class SDL2Renderer(Renderer):
    ...


class OpenGLRenderer(Renderer):
    ...


def create_renderer(name: str) -> Renderer | None:
    key = name.lower()
    if key in ("", "sdl2", "sdl"):
        return SDL2Renderer()
    if key in ("opengl", "gl"):
        return OpenGLRenderer()
    return None


def main() -> int:
    renderer = create_renderer("sdl2")
    if renderer is None:
        return 1

    if not renderer.init("Multi-Backend Demo", 960, 600):
        return 1

    input_state = InputState()

    while not input_state.quit_requested:
        renderer.pump_events(input_state)

        renderer.begin_frame(Color(22, 24, 28, 255))
        renderer.draw_filled_rect(Rect(80, 80, 90, 90), Color(255, 99, 71, 255))
        renderer.draw_filled_rect(Rect(220, 120, 120, 80), Color(255, 215, 0, 255))
        renderer.draw_filled_rect(Rect(390, 70, 60, 180), Color(70, 160, 255, 255))
        renderer.draw_filled_circle(input_state.mouse_x, input_state.mouse_y, 26, Color(80, 255, 140, 220))
        renderer.end_frame()

    renderer.shutdown()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
