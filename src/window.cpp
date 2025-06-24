#include "window.hh"
#include "chip8.hh"
#include <OpenGL/gl.h>

bool init(SDL_Window *&window, SDL_Renderer *&renderer, const char *window_title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    window = SDL_CreateWindow(window_title ? window_title : "SDL Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              680, 480,
                              0);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        return false;

    return true;
}

void mainLoop(SDL_Window *window, SDL_Renderer *renderer, Chip8 *chip8)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // ≈ 16 ms
    const int pixelSize = 10;          // Taille d’un pixel CHIP-8 à l’écran

    bool running = true;
    while (running)
    {
        uint32_t frameStart = SDL_GetTicks();

        // 1. Gérer les événements SDL (fermeture de fenêtre, clavier, etc.)
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            // TODO: gérer les touches plus tard
        }

        // 2. Faire un cycle CPU
        chip8->cycle();

        // 3. Dessiner l’écran (plus tard, avec l’opcode DRW)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
        SDL_RenderClear(renderer);

        for (int y = 0; y < 32; ++y)
        {
            for (int x = 0; x < 64; ++x)
            {
                if (chip8->getDisplay()[y * 64 + x]) // pixel allumé ?
                {
                    SDL_Rect rect = {x * pixelSize, y * pixelSize, pixelSize, pixelSize};
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(renderer);

        // 4. Attendre pour respecter 60 FPS
        uint32_t frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}