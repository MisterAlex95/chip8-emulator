#include "SDL_Display.hh"

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include <iostream>

namespace SDL
{
    SDL_Display::SDL_Display(int pixelSize)
    {
        this->pixelSize = pixelSize;
        if (!init(this->window, this->renderer, "chip8 emulator"))
            sdlFail("Erreur d'initialisation SDL/OpenGL");
    }

    SDL_Display::~SDL_Display()
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void SDL_Display::clear()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fond noir
        SDL_RenderClear(renderer);
    }

    void SDL_Display::drawPixel(int x, int y, bool on)
    {
        SDL_Rect rect = {x * pixelSize, y * pixelSize, pixelSize, pixelSize};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Blanc
        SDL_RenderFillRect(renderer, &rect);
    }

    void SDL_Display::present()
    {
        SDL_RenderPresent(renderer);
    }

    bool SDL_Display::init(SDL_Window*& window, SDL_Renderer*& renderer, const char* window_title)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            return false;

        window = SDL_CreateWindow(window_title ? window_title : "SDL Window",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
        if (!window)
            return false;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
            return false;

        return true;
    }

    void SDL_Display::sdlFail(const char* message)
    {
        std::cerr << message << "\n";
        SDL_Quit();
        exit(-1);
    }
}  // namespace SDL