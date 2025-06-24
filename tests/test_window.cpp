#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "window.hh"

TEST(WindowTest, InitAndCleanup)
{
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;

    // L'initialisation doit réussir
    ASSERT_TRUE(init(window, gl_context));
    ASSERT_NE(window, nullptr);
    ASSERT_NE(gl_context, nullptr);

    // Nettoyage sans crash
    EXPECT_NO_THROW(cleanup(window, gl_context));
}
