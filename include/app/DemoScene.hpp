#pragma once

#include "renderer/IRenderer.hpp"

namespace demo {

class DemoScene {
  public:
    void render(IRenderer& renderer, const InputState& input) const;
};

} // namespace demo
