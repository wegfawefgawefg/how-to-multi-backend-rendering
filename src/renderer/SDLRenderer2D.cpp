#include "renderer/SDLRenderer2D.hpp"

#include <SDL.h>

#include <cmath>
#include <iostream>

namespace demo {

SDLRenderer2D::~SDLRenderer2D() {
    shutdown();
}

bool SDLRenderer2D::init(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return false;
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        shutdown();
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
    }

    if (!renderer_) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        shutdown();
        return false;
    }

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    return true;
}

void SDLRenderer2D::shutdown() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        SDL_Quit();
    }
}

void SDLRenderer2D::pumpEvents(InputState& input) {
    SDL_Event event;
    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            input.quit_requested = true;
        }
    }

    SDL_GetMouseState(&input.mouse_x, &input.mouse_y);
}

void SDLRenderer2D::setDrawColor(const Color& color) {
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
}

void SDLRenderer2D::beginFrame(const Color& clear_color) {
    setDrawColor(clear_color);
    SDL_RenderClear(renderer_);
}

void SDLRenderer2D::drawFilledRect(const Rect& rect, const Color& color) {
    setDrawColor(color);
    const SDL_Rect sdl_rect{rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer_, &sdl_rect);
}

void SDLRenderer2D::drawFilledCircle(int center_x, int center_y, int radius, const Color& color) {
    setDrawColor(color);

    for (int dy = -radius; dy <= radius; ++dy) {
        const int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
        SDL_RenderDrawLine(renderer_, center_x - dx, center_y + dy, center_x + dx, center_y + dy);
    }
}

void SDLRenderer2D::endFrame() {
    SDL_RenderPresent(renderer_);
}

} // namespace demo
