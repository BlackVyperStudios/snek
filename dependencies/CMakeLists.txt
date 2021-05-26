# disable cpp-terminal library targets
set(CPPTERMINAL_BUILD_EXAMPLES OFF CACHE BOOL "don't build examples" FORCE)
set(CPPTERMINAL_ENABLE_INSTALL OFF CACHE BOOL "disable install" FORCE)
set(CPPTERMINAL_ENABLE_TESING OFF CACHE BOOL "disable testing of folf" FORCE)

# disable foxspace library targets
set(FOXSPACE_BUILD_EXAMPLES OFF CACHE BOOL "don't build examples" FORCE)
set(FOXSPACE_ENABLE_INSTALL OFF CACHE BOOL "disable install" FORCE)
set(FOXSPACE_ENABLE_TESTING OFF CACHE BOOL "disable testing of foxspace" FORCE)

add_subdirectory(cpp-terminal)
add_subdirectory(foxspace)
