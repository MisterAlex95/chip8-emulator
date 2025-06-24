#include <gtest/gtest.h>
#include "utils.hh"

TEST(UtilsTest, SdlFailExits)
{
    ASSERT_DEATH(
        {
            sdlFail("Erreur test");
        },
        "Erreur test");
}