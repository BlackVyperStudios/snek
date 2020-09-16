cmake_minimum_required(VERSION 3.17)
project(snek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncurses")

# static link windows version, or it wont run outside MSYS2 or MinGW
# A bad practise, but i doesn't work otherwise
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif (WIN32)

add_executable(snek src/main.cpp src/snake.cpp)
