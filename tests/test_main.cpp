#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "window.hh"
#include "utils.hh"

TEST(MainTest, InitAndCleanup)
{
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;

    ASSERT_TRUE(init(window, gl_context));
    ASSERT_NE(window, nullptr);
    ASSERT_NE(gl_context, nullptr);

    EXPECT_NO_THROW(cleanup(window, gl_context));
}
