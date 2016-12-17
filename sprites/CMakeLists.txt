project(Sprites)
cmake_minimum_required(VERSION 2.8)

add_definitions("-Wall -Wextra -Weffc++")
add_definitions("-std=c++1z")
find_package(SFML 2 REQUIRED system window graphics)

add_executable(run
src/game.cpp
src/main.cpp)

target_link_libraries(run ${SFML_LIBRARIES})
