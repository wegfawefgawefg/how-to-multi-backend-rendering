#include <iostream>
#include <memory>
#include <string>

#include "app/DemoScene.hpp"
#include "renderer/RendererFactory.hpp"

int main(int argc, char** argv) {
    std::string backend = "sdl2";
    if (argc >= 2) {
        backend = argv[1];
    }

    std::unique_ptr<demo::IRenderer> renderer = demo::createRenderer(backend);
    if (!renderer) {
        std::cerr << "Unsupported backend: " << backend << "\n";
        std::cerr << "Available backend(s): sdl2\n";
        return 1;
    }

    if (!renderer->init("Multi-Backend Rendering Demo", 960, 600)) {
        std::cerr << "Failed to initialize renderer backend.\n";
        return 1;
    }

    demo::DemoScene scene;
    demo::InputState input;

    while (!input.quit_requested) {
        renderer->pumpEvents(input);
        scene.render(*renderer, input);
    }

    renderer->shutdown();
    return 0;
}
