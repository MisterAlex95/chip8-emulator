#include "window.hh"
#include "chip8.hh"
#include <OpenGL/gl.h>

bool init(SDL_Window *&window, SDL_GLContext &gl_context, const char *window_title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    window = SDL_CreateWindow(window_title ? window_title : "SDL OpenGL Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              680, 480,
                              SDL_WINDOW_OPENGL);
    if (!window)
        return false;

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context)
        return false;

    return true;
}

void mainLoop(SDL_Window *window, Chip8 *chip8)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // ≈ 16 ms

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

        // 4. Attendre pour respecter 60 FPS
        uint32_t frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void cleanup(SDL_Window *window, SDL_GLContext gl_context)
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(gl_context);
    SDL_Quit();
}