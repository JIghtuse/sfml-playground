project(SFMLHello)
cmake_minimum_required(VERSION 2.8)

add_definitions("-Wall -Wextra -Weffc++")
add_definitions("-std=c++1z")
find_package(SFML 2 REQUIRED system window graphics)

add_executable(hello src/hello.cpp)
target_link_libraries(hello ${SFML_LIBRARIES})
