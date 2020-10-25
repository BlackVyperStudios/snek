cmake_minimum_required(VERSION 3.16)
project(snek
        VERSION 1.0.2
        DESCRIPTION "SNEK - A simple snake clone, playable in the commandline with some unique game modes."
        HOMEPAGE_URL "https://github.com/MCWertGaming/snek"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
configure_file(src-old/information.hpp.in src-old/information.hpp)

# static link windows version, or it wont run outside MSYS2 or MinGW
# A bad practise, but i doesn't work otherwise
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif (WIN32)

set(snake-source src-old/snake.cpp src-old/utils.cpp)

add_executable(snek-debugFront src-old/frontend-debug.cpp ${snake-source})
target_include_directories(snek-debugFront PUBLIC ${PROJECT_BINARY_DIR}/src-old)
target_link_libraries(snek-debugFront ncurses)

add_executable(snek-releaseFront src-old/frontend-release.cpp ${snake-source})
target_include_directories(snek-releaseFront PUBLIC ${PROJECT_BINARY_DIR}/src-old)
target_link_libraries(snek-releaseFront ncurses)
