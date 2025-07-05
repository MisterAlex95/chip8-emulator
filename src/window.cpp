#include "window.hh"
#include "core/Chip8.hh"

#include "interfaces/IDisplay.hh"
#include "interfaces/IInput.hh"
#include "interfaces/ITimer.hh"

void
mainLoop(chip8::Chip8* chip8, IInput& input, IDisplay& display, ITimer& timer)
{
    const int FPS        = 60;
    const int frameDelay = 1000 / FPS;  // ≈ 16 ms

    bool running = true;
    while (running)
    {
        uint32_t frameStart = timer.getTicks();

        // Event Loop
        auto keyboard = chip8->getKeyboard();
        input.pollEvents(keyboard, running);

        // CPU Cycle
        chip8->cycle();

        // Clear before drawing
        display.clear();

        // Drawing the screen
        for (int y = 0; y < chip8::config::DISPLAY_Y; ++y)
        {
            for (int x = 0; x < chip8::config::DISPLAY_X; ++x)
            {
                if (chip8->getDisplay()->isPixelEnable(x, y))
                {
                    display.drawPixel(x, y, true);
                }
            }
        }

        display.present();

        // Limit at 60fps
        uint32_t frameTime = timer.getTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            timer.waitUntilNextFrame(frameDelay - frameTime);
        }
    }
}