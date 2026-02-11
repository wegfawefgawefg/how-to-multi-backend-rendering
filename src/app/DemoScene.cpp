#include "app/DemoScene.hpp"

namespace demo {

void DemoScene::render(IRenderer& renderer, const InputState& input) const {
    renderer.beginFrame(Color{22, 24, 28, 255});

    renderer.drawFilledRect(Rect{80, 80, 90, 90}, Color{255, 99, 71, 255});
    renderer.drawFilledRect(Rect{220, 120, 120, 80}, Color{255, 215, 0, 255});
    renderer.drawFilledRect(Rect{390, 70, 60, 180}, Color{70, 160, 255, 255});

    renderer.drawFilledCircle(input.mouse_x, input.mouse_y, 26, Color{80, 255, 140, 220});

    renderer.endFrame();
}

} // namespace demo
