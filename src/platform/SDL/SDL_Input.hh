#ifndef SDL_INPUT_HH
#define SDL_INPUT_HH

#include "interfaces/IInput.hh"

namespace SDL
{
    class SDL_Input : public IInput
    {
       public:
        void pollEvents(const chip8::IKeyboard* keyboard, bool& quitFlag) override;
    };
};  // namespace SDL

#endif  // SDL_INPUT_HH
