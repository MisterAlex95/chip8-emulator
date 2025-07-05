#ifndef CHIP8_EVENT_HH
#define CHIP8_EVENT_HH

#include "Types.hh"

#include <iostream>

namespace chip8
{
    class Event
    {
       public:
        enum class Type : uint8_t
        {
            None,
            Quit,
            KeyDown,
            KeyUp,
            KeyRight,
            KeyLeft,
        };

        Event() : type(Type::None), key(chip8::Key::Num0) {}
        explicit Event(Type t) : type(t), key(chip8::Key::Num0) {}
        Event(Type t, chip8::Key k) : type(t), key(k) {}

        [[nodiscard]] Type       getType() const { return type; }
        [[nodiscard]] chip8::Key getKey() const { return key; }

       private:
        Type       type;
        chip8::Key key;
    };

}  // namespace chip8

#endif  // CHIP8_EVENT_HH
