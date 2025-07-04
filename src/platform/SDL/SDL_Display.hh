#ifndef SDL_DISPLAY_HH
#define SDL_DISPLAY_HH

#include <SDL_render.h>

#include "interfaces/IDisplay.hh"

namespace SDL
{
    class SDL_Display : public IDisplay
    {
       public:
        SDL_Display(int pixelSize);
        ~SDL_Display();

        void clear() override;
        void drawPixel(int x, int y, bool on) override;
        void present() override;

       private:
        bool init(SDL_Window*& window, SDL_Renderer*& renderer, const char* window_title);
        void sdlFail(const char* message);

        int           pixelSize;
        SDL_Window*   window{};
        SDL_Renderer* renderer{};
    };
}  // namespace SDL
#endif  // SDL_DISPLAY_HH
