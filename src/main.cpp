#include "window.hh"
#include "utils.hh"

int main()
{
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;

    if (!init(window, gl_context))
        sdlFail("Erreur d'initialisation SDL/OpenGL");

    mainLoop(window);
    cleanup(window, gl_context);

    return 0;
}