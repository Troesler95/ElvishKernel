# enable cross-compiling by setting
# system globals manually
set(CMAKE_SYSTEM_NAME GENERIC)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(TARGET i686-elf)
message(STATUS "compiler id: " ${CMAKE_C_COMPILER_ID})

# force compiler to the cross compiler
include(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(i686-elf-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(i686-elf-g++ GNU)
CMAKE_C_LINK_EXECUTABLE(i686-elf-ld)
message(STATUS "after force: " ${CMAKE_C_COMPILER_ID})

# these prevent the compiler from looking on
# the host computer to resolve linking errors
# (i.e. looking in the STL for a call to a member)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
