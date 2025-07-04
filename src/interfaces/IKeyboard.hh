#ifndef CHIP8_IKEYBOARD_HH
#define CHIP8_IKEYBOARD_HH

#include "core/Event.hh"

#include <array>

namespace chip8
{
    class IKeyboard
    {
       public:
        virtual ~IKeyboard() = default;

        virtual void               setKeyState(uint8_t key, bool pressed) = 0;
        virtual void               handleEvent(const Event& event)        = 0;
        virtual void               reset()                                = 0;
        [[nodiscard]] virtual bool isKeyPressed(uint8_t key) const        = 0;
        [[nodiscard]] virtual const std::array<bool, 16>& getKeys() const = 0;
    };

}  // namespace chip8

#endif  // CHIP8_IKEYBOARD_HH
