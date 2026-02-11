#pragma once

#include "renderer/IRenderer.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace demo {

class SDLRenderer2D final : public IRenderer {
  public:
    SDLRenderer2D() = default;
    ~SDLRenderer2D() override;

    bool init(const std::string& title, int width, int height) override;
    void shutdown() override;

    void pumpEvents(InputState& input) override;

    void beginFrame(const Color& clear_color) override;
    void drawFilledRect(const Rect& rect, const Color& color) override;
    void drawFilledCircle(int center_x, int center_y, int radius, const Color& color) override;
    void endFrame() override;

  private:
    void setDrawColor(const Color& color);

    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
};

} // namespace demo
