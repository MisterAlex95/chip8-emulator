#include <array>

#include "Constants.hh"
#include "Display.hh"

chip8::Display::Display()
{
    _display.fill(false);
}

[[nodiscard]] bool
chip8::Display::isPixelEnable(const int x, const int y) const
{
    return _display[y * chip8::config::DISPLAY_X + x];
}

void
chip8::Display::clear()
{
    _display.fill(false);
}

[[nodiscard]] int
chip8::Display::getSize() const
{
    return _display.size();
}

void
chip8::Display::setDisplayAt(std::size_t index, bool value)
{
    if (index < _display.size())
    {
        _display[index] = value;
    }
}

void
chip8::Display::setDisplayAt(int x, int y, bool value)
{
    if (x >= 0 && x < chip8::config::DISPLAY_X && y >= 0 && y < chip8::config::DISPLAY_Y)
    {
        _display[y * chip8::config::DISPLAY_X + x] = value;
    }
}