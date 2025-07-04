#ifndef CHIP8_EVENT_HH
#define CHIP8_EVENT_HH

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

        Event() : type(Type::None), key(0) {}
        explicit Event(Type t) : type(t), key(0) {}
        Event(Type t, uint8_t k) : type(t), key(k) {}

        [[nodiscard]] Type    getType() const { return type; }
        [[nodiscard]] uint8_t getKey() const { return key; }

       private:
        Type    type;
        uint8_t key;
    };

}  // namespace chip8

#endif  // CHIP8_EVENT_HH
