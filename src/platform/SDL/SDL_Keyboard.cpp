#include "SDL_Keyboard.hh"

namespace SDL
{

    SDL_Keyboard::SDL_Keyboard()
    {
        this->SDL_Keyboard::reset();
    }

    void SDL_Keyboard::handleEvent(const SDL_Event& event)
    {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            bool pressed = (event.type == SDL_KEYDOWN);
            auto mapped  = mapSDLKey(event.key.keysym.sym);
            if (mapped.has_value())
            {
                setKeyState(mapped.value(), pressed);
            }
        }
    }

    void SDL_Keyboard::setKeyState(const uint8_t key, const bool pressed)
    {
        if (key <= this->_keys.size())
        {
            this->_keys[key] = pressed;
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

    std::optional<uint8_t> SDL_Keyboard::mapSDLKey(SDL_Keycode key)
    {
        switch (key)
        {
            case SDLK_1:
                return 0x1;
            case SDLK_2:
                return 0x2;
            case SDLK_3:
                return 0x3;
            case SDLK_4:
                return 0xC;

            case SDLK_q:
                return 0x4;
            case SDLK_w:
                return 0x5;
            case SDLK_e:
                return 0x6;
            case SDLK_r:
                return 0xD;

            case SDLK_a:
                return 0x7;
            case SDLK_s:
                return 0x8;
            case SDLK_d:
                return 0x9;
            case SDLK_f:
                return 0xE;

            case SDLK_z:
                return 0xA;
            case SDLK_x:
                return 0x0;
            case SDLK_c:
                return 0xB;
            case SDLK_v:
                return 0xF;

            default:
                return std::nullopt;
        }
    }
}  // namespace SDL