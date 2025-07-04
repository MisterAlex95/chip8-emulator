#include "core/Keyboard.hh"
#include <iostream>

namespace chip8
{

    Keyboard::Keyboard()
    {
        Keyboard::reset();
    }

    void Keyboard::handleEvent(const Event& event)
    {
        switch (event.getType())
        {
            case chip8::Event::Type::KeyDown:
                _keys[static_cast<size_t>(event.getKey())] = true;
                break;
            case chip8::Event::Type::KeyUp:
                _keys[static_cast<size_t>(event.getKey())] = false;
                break;
            default:
                break;
        }
        printKeysState();
    }

    void Keyboard::printKeysState() const
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

    void Keyboard::setKeyState(chip8::Key key, bool pressed)
    {
        if (static_cast<uint8_t>(key) < _keys.size())
        {
            _keys[static_cast<uint8_t>(key)] = pressed;
        }
        else
        {
#ifdef DEV_MODE
            std::cerr << "[Keyboard] Touche invalide : " << static_cast<int>(key) << "\n";
#endif
        }
    }

    bool Keyboard::isKeyPressed(uint8_t key) const
    {
        if (key < _keys.size())
        {
            return _keys[key];
        }
        else
        {
#ifdef DEV_MODE
            std::cerr << "[Keyboard] Touche invalide (isKeyPressed) : " << static_cast<int>(key)
                      << "\n";
#endif
            return false;
        }
    }

    const std::array<bool, 16>& Keyboard::getKeys() const
    {
        return _keys;
    }

    void Keyboard::reset()
    {
        _keys.fill(false);
    }

}  // namespace chip8
