cmake_minimum_required(VERSION 3.17)
project(snek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_CXX_FLAGS "-static -lncurses")

add_executable(snek src/main.cpp)