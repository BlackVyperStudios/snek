# disable cpp-terminal library targets
set(CPPTERMINAL_BUILD_EXAMPLES OFF CACHE BOOL "don't build examples" FORCE)
set(CPPTERMINAL_ENABLE_INSTALL OFF CACHE BOOL "disable install" FORCE)
set(CPPTERMINAL_ENABLE_TESING OFF CACHE BOOL "disable testing of folf" FORCE)

# disable FOLF-namespace library targets
set(FOLF_BUILD_EXAMPLES OFF CACHE BOOL "don't build examples" FORCE)
set(FOLF_ENABLE_INSTALL OFF CACHE BOOL "disable install" FORCE)
set(FOLF_ENABLE_TESTING OFF CACHE BOOL "disable testing of folf" FORCE)

add_subdirectory(cpp-terminal)
add_subdirectory(folf-namespace)
