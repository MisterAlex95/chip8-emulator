#include "SDL_Keyboard.hh"

namespace SDL
{

    SDL_Keyboard::SDL_Keyboard()
    {
        this->SDL_Keyboard::reset();
    }

    void SDL_Keyboard::handleEvent(const chip8::Event& event)
    {
        if (event.getType() == chip8::Event::Type::KeyDown ||
            event.getType() == chip8::Event::Type::KeyUp)
        {
            const bool pressed = (event.getType() == chip8::Event::Type::KeyDown);
            const auto mapped  = event.getKey();
            setKeyState(mapped, pressed);
        }
    }

    void SDL_Keyboard::setKeyState(const chip8::Key key, const bool pressed)
    {
        if (static_cast<uint8_t>(key) <= this->_keys.size())
        {
            this->_keys[static_cast<uint8_t>(key)] = pressed;
        }
    }

    [[nodiscard]] bool SDL_Keyboard::isKeyPressed(uint8_t key) const
    {
        return key < _keys.size() ? _keys[key] : false;
    }

    [[nodiscard]] const std::array<bool, 16>& SDL_Keyboard::getKeys() const
    {
        return this->_keys;
    }

    void SDL_Keyboard::reset()
    {
        this->_keys.fill(false);
    }

    std::optional<chip8::Key> SDL_Keyboard::mapSDLKey(SDL_Keycode key)
    {
        switch (key)
        {
            case SDLK_1:
                return chip8::Key::Num1;
            case SDLK_2:
                return chip8::Key::Num2;
            case SDLK_3:
                return chip8::Key::Num3;
            case SDLK_4:
                return chip8::Key::Num4;

            case SDLK_q:
                return chip8::Key::Num5;
            case SDLK_w:
                return chip8::Key::Num5;
            case SDLK_e:
                return chip8::Key::Num6;
            case SDLK_r:
                return chip8::Key::NumD;

            case SDLK_a:
                return chip8::Key::Num7;
            case SDLK_s:
                return chip8::Key::Num8;
            case SDLK_d:
                return chip8::Key::Num9;
            case SDLK_f:
                return chip8::Key::NumE;

            case SDLK_z:
                return chip8::Key::NumA;
            case SDLK_x:
                return chip8::Key::Num0;
            case SDLK_c:
                return chip8::Key::NumB;
            case SDLK_v:
                return chip8::Key::NumF;

            default:
                return std::nullopt;
        }
    }
}  // namespace SDL