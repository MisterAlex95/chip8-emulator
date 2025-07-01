#ifndef DISPLAY_HH
#define DISPLAY_HH

#include <array>

#include "Constants.hh"

namespace chip8
{
    class Display
    {
       public:
        Display();

        void                    clean();
        void                    setDisplayAt(std::size_t index, bool value);
        void                    setDisplayAt(int x, int y, bool value);

        [[nodiscard]] int  getSize() const;
        [[nodiscard]] bool isPixelEnable(int x, int y) const;

       private:
        std::array<bool, chip8::config::DISPLAY_Y * chip8::config::DISPLAY_X>
            _display;  // 64x32 pixel display

    };

}  // namespace chip8

#endif  // DISPLAY_HH
