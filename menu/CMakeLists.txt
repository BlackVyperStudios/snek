# list of sourcefiles
set(menu-source menu.cpp
                 visual.cpp)

# create a compile target for FOLF
add_library(menulib ${menu-source})
target_link_libraries(menulib PRIVATE cpp-terminal snakelib folf-namespace)
target_include_directories(menulib INTERFACE ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})
set_target_properties(menulib PROPERTIES
        PUBLIC_HEADER "menu/menu.hpp")
    