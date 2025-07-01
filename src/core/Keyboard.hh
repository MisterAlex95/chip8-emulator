#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include <cstdint>

#include "Types.hh"

namespace chip8
{
    class Keyboard
    {
       public:
        Keyboard();

       private:
        KeypadArray _keys;  // Keypad
    };

}  // namespace chip8

#endif  // KEYBOARD_HH
