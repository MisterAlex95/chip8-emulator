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

        void                                      handleEvent(const SDL_Event& event);
        void                                      handleEvent(const chip8::Event& event);
        void                                      setKeyState(uint8_t key, bool pressed) override;
        [[nodiscard]] bool                        isKeyPressed(uint8_t key) const override;
        [[nodiscard]] const std::array<bool, 16>& getKeys() const override;

        void reset() override;

       private:
        std::array<bool, 16> _keys{};

        static std::optional<uint8_t> mapSDLKey(SDL_Keycode key);
    };

}  // namespace SDL

#endif  // SDL_KEYBOARD_HH
