# include cmake modules
include(FetchContent)

# download folf-namespace library
FetchContent_Declare(folf_namespace
        GIT_REPOSITORY https://github.com/FOLF-projects/folf-namespace.git
        GIT_TAG main
)
FetchContent_GetProperties(folf_namespace)
if(NOT folf_namespace_POPULATED)
        FetchContent_Populate(folf_namespace)
        add_subdirectory(${folf_namespace_SOURCE_DIR} ${folf_namespace_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# download folf-namespace library
FetchContent_Declare(cpp_terminal
        GIT_REPOSITORY https://github.com/jupyter-xeus/cpp-terminal.git
        GIT_TAG master
)
FetchContent_GetProperties(cpp_terminal)
if(NOT cpp_terminal)
        FetchContent_Populate(cpp_terminal)
        add_subdirectory(${cpp_terminal_SOURCE_DIR} ${cpp_terminal_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
