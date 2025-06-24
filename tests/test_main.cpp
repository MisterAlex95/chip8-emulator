#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "window.hh"
#include "utils.hh"

TEST(MainTest, InitAndCleanup)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    ASSERT_TRUE(init(window, renderer, "test"));
    ASSERT_NE(window, nullptr);
    ASSERT_NE(renderer, nullptr);

    EXPECT_NO_THROW(cleanup(window, renderer));
}
