#include "window.hh"
#include <OpenGL/gl.h>

bool init(SDL_Window *&window, SDL_GLContext &gl_context)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    window = SDL_CreateWindow("SDL2 Window",
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

void mainLoop(SDL_Window *window)
{
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
}

void cleanup(SDL_Window *window, SDL_GLContext gl_context)
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(gl_context);
    SDL_Quit();
}