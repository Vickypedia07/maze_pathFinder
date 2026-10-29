cmake_minimum_required(VERSION 3.20)
project(pathfinding_visualizer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-Wall -Wextra)

add_library(pathlib src/grid.cpp src/pathfinder.cpp src/maze.cpp)
target_include_directories(pathlib PUBLIC src)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(pathfinder src/main.cpp src/renderer.cpp)
target_link_libraries(pathfinder PRIVATE pathlib SFML::Graphics)

include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.5.2)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(tests tests/test_pathfinder.cpp)
target_link_libraries(tests PRIVATE pathlib Catch2::Catch2WithMain)
add_test(NAME tests COMMAND tests)