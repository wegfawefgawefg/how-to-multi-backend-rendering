#include <iostream>
#include <memory>
#include <string>

#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "app/DemoScene.hpp"
#include "renderer/RendererFactory.hpp"

#ifdef __EMSCRIPTEN__
struct LoopContext {
    demo::IRenderer* renderer;
    demo::DemoScene* scene;
    demo::InputState* input;
};

static void emscripten_loop(void* arg) {
    auto* ctx = static_cast<LoopContext*>(arg);
    ctx->renderer->pumpEvents(*ctx->input);
    ctx->scene->render(*ctx->renderer, *ctx->input);
}
#endif

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

#ifdef __EMSCRIPTEN__
    LoopContext ctx{renderer.get(), &scene, &input};
    emscripten_set_main_loop_arg(emscripten_loop, &ctx, 0, 1);
#else
    while (!input.quit_requested) {
        renderer->pumpEvents(input);
        scene.render(*renderer, input);
    }
#endif

    renderer->shutdown();
    return 0;
}
