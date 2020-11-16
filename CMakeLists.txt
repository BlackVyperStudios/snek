cmake_minimum_required(VERSION 3.16)
project(snek
        VERSION 1.1.0
        DESCRIPTION "SNEK - A simple snake clone, playable in the commandline with some unique game modes."
        HOMEPAGE_URL "https://github.com/BlackVyperStudios/snek"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
configure_file(src/information.hpp.in src/information.hpp)

# cpp-terminal dependency
add_library(cpp-terminal INTERFACE)
target_include_directories(cpp-terminal INTERFACE ${PROJECT_SOURCE_DIR}/dependencies/cpp-terminal)
set_target_properties(cpp-terminal PROPERTIES
    PUBLIC_HEADER "cpp-terminal/terminal.h;cpp-terminal/terminal_base.h")

# snake sources
set(snake-source src/snake.cpp src/utils.cpp)

# test target
add_executable(test src/main.cpp src/menu.cpp src/utils.cpp src/visual.cpp)
target_include_directories(test PUBLIC ${PROJECT_BINARY_DIR}/src)
target_link_libraries(test cpp-terminal)
