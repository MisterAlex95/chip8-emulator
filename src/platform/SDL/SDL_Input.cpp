#include "SDL_Input.hh"
#include "SDL_Keyboard.hh"

#include <SDL_events.h>

namespace SDL
{
    void SDL_Input::pollEvents(const chip8::IKeyboard* keyboard, bool& quitFlag)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quitFlag = false;

            // keyboard->handleEvent(event);
        }
    }
}  // namespace SDL
