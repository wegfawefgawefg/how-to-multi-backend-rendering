#pragma once

#include <cstdint>
#include <string>

namespace demo {

struct Color {
    std::uint8_t r = 255;
    std::uint8_t g = 255;
    std::uint8_t b = 255;
    std::uint8_t a = 255;
};

struct Rect {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

struct InputState {
    bool quit_requested = false;
    int mouse_x = 0;
    int mouse_y = 0;
};

class IRenderer {
  public:
    virtual ~IRenderer() = default;

    virtual bool init(const std::string& title, int width, int height) = 0;
    virtual void shutdown() = 0;

    virtual void pumpEvents(InputState& input) = 0;

    virtual void beginFrame(const Color& clear_color) = 0;
    virtual void drawFilledRect(const Rect& rect, const Color& color) = 0;
    virtual void drawFilledCircle(int center_x, int center_y, int radius, const Color& color) = 0;
    virtual void endFrame() = 0;
};

} // namespace demo
