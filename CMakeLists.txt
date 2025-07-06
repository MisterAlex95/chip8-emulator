cmake_minimum_required(VERSION 3.10)
project(chip8-emulator)

# === OPTION DEV_MODE (Debug, Warnings, etc.) ===
option(DEV_MODE "Activer les options de développement (debug, warnings...)" OFF)

if (DEV_MODE)
    message(STATUS "🔧 Mode développement activé (DEV_MODE=ON)")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    add_compile_definitions(DEV_MODE=1)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -pedantic")
else ()
    message(STATUS "🚀 Mode production (DEV_MODE=OFF)")
endif ()

# === Configuration générale ===
set(PROJECT_NAME "chip8")
set(PROJECT_NAME_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Dépendances ===
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GTest REQUIRED)

# === Exécutable principal ===
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/window.cpp
        src/core/Timers.cpp
        src/core/Chip8.cpp
        src/core/CPU.cpp
        src/core/Display.cpp
        src/core/Memory.cpp
        src/interfaces/IKeyboard.hh
        src/platform/SDL/SDL_Keyboard.cpp
        src/platform/SDL/SDL_Keyboard.hh
        src/core/Event.hh
        src/interfaces/IWindow.hh
        src/interfaces/IDisplay.hh
        src/interfaces/ITimer.hh
        src/interfaces/IInput.hh
        src/platform/SDL/SDL_Input.cpp
        src/platform/SDL/SDL_Input.hh
        src/platform/SDL/SDL_Display.cpp
        src/platform/SDL/SDL_Display.hh
        src/platform/SDL/SDL_Timer.cpp
        src/platform/SDL/SDL_Timer.hh
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        src
)

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

# === Partie tests ===
enable_testing()

# Tous les tests normaux
add_executable(tests_all
        tests/test_all.cpp
        tests/test_window.cpp
        tests/test_main.cpp
        tests/test_chip8.cpp
        src/window.cpp
        src/core/Timers.cpp
        src/core/Chip8.cpp
        src/core/CPU.cpp
        src/core/Display.cpp
        src/core/Memory.cpp
        src/interfaces/IKeyboard.hh
        src/platform/SDL/SDL_Keyboard.cpp
        src/platform/SDL/SDL_Keyboard.hh
        src/core/Event.hh
        src/interfaces/IDisplay.hh
        src/platform/SDL/SDL_Input.cpp
        src/platform/SDL/SDL_Input.hh
        src/platform/SDL/SDL_Display.cpp
        src/platform/SDL/SDL_Display.hh
)

target_include_directories(tests_all PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${GTEST_INCLUDE_DIRS}
        src
)

target_link_libraries(tests_all
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        GTest::GTest
        GTest::Main
)

target_compile_definitions(tests_all PRIVATE GL_SILENCE_DEPRECATION)
add_test(NAME all_tests COMMAND tests_all)

# === Tests spécifiques (utils death tests) ===
add_executable(tests_utils_death
        tests/test_utils.cpp
        src/interfaces/IKeyboard.hh
        src/platform/SDL/SDL_Keyboard.cpp
        src/platform/SDL/SDL_Keyboard.hh
        src/core/Event.hh
        src/interfaces/IDisplay.hh
        src/platform/SDL/SDL_Input.cpp
        src/platform/SDL/SDL_Input.hh
        src/platform/SDL/SDL_Display.cpp
        src/platform/SDL/SDL_Display.hh
)

target_include_directories(tests_utils_death PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        src
)

target_link_libraries(tests_utils_death
        GTest::GTest
        GTest::Main
        ${SDL2_LIBRARIES}
)

add_test(NAME utils_death_tests COMMAND tests_utils_death)
