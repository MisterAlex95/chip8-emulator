#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "window.hh"

TEST(WindowTest, InitAndCleanup)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // L'initialisation doit réussir
    ASSERT_TRUE(init(window, renderer, "test"));
    ASSERT_NE(window, nullptr);
    ASSERT_NE(renderer, nullptr);

    // Nettoyage sans crash
    EXPECT_NO_THROW(cleanup(window, renderer));
}
