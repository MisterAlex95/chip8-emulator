#include "core/Chip8.hh"
#include "utils.hh"
#include "window.hh"

#ifdef DEV_MODE
#include <iostream>
#endif

using namespace chip8;

int
main(int argc, char** argv)
{
#ifdef DEV_MODE
    std::cout << "[DEBUG MODE] with " << argc << " arguments\n";
#endif

    SDL_Window*   window = nullptr;
    SDL_Renderer* renderer;

    if (!init(window, renderer, "chip8 emulator"))
        sdlFail("Erreur d'initialisation SDL/OpenGL");

    auto* chip8 = new Chip8();
    chip8->loadFontSet();

    if (chip8->loadROM(argv[1]))
    {
        mainLoop(window, renderer, chip8);
    }

    cleanup(window, renderer);

    return 0;
}