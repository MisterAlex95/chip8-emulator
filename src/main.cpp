#include "window.hh"
#include "utils.hh"
#include "chip8.hh"
#include <iostream>

int main(int argc, char **argv)
{
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;

    if (!init(window, gl_context, "chip8 emulator"))
        sdlFail("Erreur d'initialisation SDL/OpenGL");

    Chip8 *chip8 = new Chip8();
    chip8->initialize();
    chip8->loadROM(argv[1]);

    //    mainLoop(window);
    cleanup(window, gl_context);

    return 0;
}