#ifndef IINPUT_HH
#define IINPUT_HH

#include "IKeyboard.hh"

class IInput
{
   public:
    virtual ~IInput()                                                  = default;
    virtual void pollEvents(const chip8::IKeyboard* keyboard, bool& quitFlag) = 0;
};

#endif  // IINPUT_HH
