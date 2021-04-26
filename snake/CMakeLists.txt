# configure information header
configure_file(info.hpp.in info.hpp)

# list of sourcefiles
set(snake-source snake.cpp)

# create a compile target for FOLF
add_library(snakelib ${snake-source})
target_link_libraries(snakelib PRIVATE cpp-terminal)
target_include_directories(snakelib PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
set_target_properties(snakelib PROPERTIES
        PUBLIC_HEADER "snake/snake.hpp;snake/info.hpp")
