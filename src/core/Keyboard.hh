#ifndef CHIP8_KEYBOARD_HH
#define CHIP8_KEYBOARD_HH

#include "interfaces//IKeyboard.hh"

#include <array>
#include <cstdint>

namespace chip8
{

    class Keyboard final : public IKeyboard
    {
       public:
        Keyboard();
        ~Keyboard() override = default;

        void               handleEvent(const Event& event) override;
        void               setKeyState(chip8::Key key, bool pressed) override;
        [[nodiscard]] bool isKeyPressed(uint8_t key) const override;
        [[nodiscard]] const std::array<bool, 16>& getKeys() const override;
        void                                      reset() override;

       private:
        std::array<bool, 16> _keys{};
    };

}  // namespace chip8

#endif  // CHIP8_KEYBOARD_HH
