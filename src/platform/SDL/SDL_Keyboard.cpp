#include "SDL_Keyboard.hh"
#include <iostream>
#include <string>

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
        if (static_cast<size_t>(key) <= this->_keys.size())
        {
            this->_keys[static_cast<size_t>(key)] = pressed;
            // printKeysState();
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

    std::string keycodeToString(SDL_Keycode key)
    {
        // Lettres minuscules
        if (key >= SDLK_a && key <= SDLK_z)
        {
            return std::string(1, static_cast<char>(key));
        }
        // Chiffres 0-9
        else if (key >= SDLK_0 && key <= SDLK_9)
        {
            return std::string(1, static_cast<char>(key));
        }
        else
        {
            // Pour les autres touches, tu peux retourner le code hexa par ex.
            return "Keycode: 0x" + std::to_string(key);
        }
    }

    void SDL_Keyboard::printKeysState() const
    {
        std::cout << "Keys state: ";
        for (size_t i = 0; i < _keys.size(); ++i)
        {
            // Affiche 1 si la touche est pressée, 0 sinon
            std::cout << (_keys[i] ? '1' : '0');
            if (i < _keys.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::optional<chip8::Key> SDL_Keyboard::mapSDLKey(SDL_Keycode key)
    {
        std::cout << "Key pressed: " << keycodeToString(key) << std::endl;

        switch (key)
        {
            case SDLK_0:
                return chip8::Key::Num0;
            case SDLK_1:
                return chip8::Key::Num1;
            case SDLK_2:
                return chip8::Key::Num2;
            case SDLK_3:
                return chip8::Key::Num3;
            case SDLK_4:
                return chip8::Key::Num4;
            case SDLK_5:
                return chip8::Key::Num5;
            case SDLK_6:
                return chip8::Key::Num6;
            case SDLK_7:
                return chip8::Key::Num7;
            case SDLK_8:
                return chip8::Key::Num8;
            case SDLK_9:
                return chip8::Key::Num9;

            case SDLK_a:
                return chip8::Key::NumA;
            case SDLK_b:
                return chip8::Key::NumB;
            case SDLK_c:
                return chip8::Key::NumC;
            case SDLK_d:
                return chip8::Key::NumD;
            case SDLK_e:
                return chip8::Key::NumE;
            case SDLK_f:
                return chip8::Key::NumF;

            default:
                std::cout << "Not catch " << keycodeToString(key) << std::endl;
                return std::nullopt;
        }
    }
}  // namespace SDL