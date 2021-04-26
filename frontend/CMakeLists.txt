# main game file for releases
add_executable(snek snek.cpp)
target_link_libraries(snek cpp-terminal menulib)
# testing version without the game menu
add_executable(snek-standalone snek-standalone.cpp)
target_link_libraries(snek-standalone cpp-terminal snakelib)
