#ifndef SDL_KEYBOARD_HH
#define SDL_KEYBOARD_HH

#include <SDL_events.h>

#include "interfaces/IKeyboard.hh"

namespace SDL
{
    class SDL_Keyboard : public chip8::IKeyboard
    {
       public:
        SDL_Keyboard();
        ~SDL_Keyboard() override = default;

        void               handleEvent(const chip8::Event& event) override;
        void               setKeyState(chip8::Key key, bool pressed) override;
        [[nodiscard]] bool isKeyPressed(uint8_t key) const override;
        [[nodiscard]] const std::array<bool, 16>& getKeys() const override;

        void reset() override;

        static std::optional<chip8::Key> mapSDLKey(SDL_Keycode key);

       private:
        void printKeysState() const;

        std::array<bool, 16> _keys{};
    };

}  // namespace SDL

#endif  // SDL_KEYBOARD_HH
