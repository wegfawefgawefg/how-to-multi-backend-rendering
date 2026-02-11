#include "renderer/RendererFactory.hpp"

#include <algorithm>
#include <cctype>

#include "renderer/SDLRenderer2D.hpp"

namespace demo {

static std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

std::unique_ptr<IRenderer> createRenderer(const std::string& backend_name) {
    const std::string backend = toLower(backend_name);

    if (backend.empty() || backend == "sdl2" || backend == "sdl") {
        return std::make_unique<SDLRenderer2D>();
    }

    return nullptr;
}

} // namespace demo
