cmake_minimum_required(VERSION 3.10)
project(chip8-emulator)

set(PROJECT_NAME "chip8")
set(PROJECT_NAME_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/utils.cpp
    src/window.cpp
    src/chip8.cpp
)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_NAME_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)

# === Partie tests ===
enable_testing()

# Exécutable principal pour tous les tests SAUF les death tests
add_executable(tests_all
    tests/test_all.cpp
    tests/test_window.cpp
    tests/test_main.cpp
    tests/test_chip8.cpp
    src/window.cpp
    src/chip8.cpp
    src/utils.cpp
)

target_include_directories(tests_all PRIVATE ${SDL2_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} src)
target_link_libraries(tests_all ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} GTest::GTest GTest::Main)
target_compile_definitions(tests_all PRIVATE GL_SILENCE_DEPRECATION)
add_test(NAME all_tests COMMAND tests_all)

# Exécutable séparé pour les death tests (test_utils)
add_executable(tests_utils_death
    tests/test_utils.cpp
    src/utils.cpp
)
target_include_directories(tests_utils_death PRIVATE ${GTEST_INCLUDE_DIRS} src ${SDL2_INCLUDE_DIRS})
target_link_libraries(tests_utils_death GTest::GTest GTest::Main ${SDL2_LIBRARIES})
add_test(NAME utils_death_tests COMMAND tests_utils_death)
