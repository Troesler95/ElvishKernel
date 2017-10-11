cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# disable error for CYGWIN users
set(CMAKE_LEGACY_CYGWIN32_WIN32 0)
# for now, name the project generically
project(Microkernel C CXX)

# Version number for development
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)
message(STATUS "crosscompiling: ${CMAKE_CROSSCOMPILING}")
if(NOT CMAKE_CROSSCOMPILING)
	message(FATAL_ERROR "This script must be run with the \
	-DCMAKE_TOOLCHAIN_FILE=<filename.cmake> in order to run properly!")
endif()

# determine the type of compiler we are using
# we need to be sure that it is the cross-compiler,
# or else the kernel won't be bootable by GRUB probably
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(COMPILER_FLAGS "-Wall -Wextra -Werror -ffreestanding -O2"
		CACHE STRING "")
else()
		message(FATAL_ERROR "\
						ERROR: This project needs to be executed with \
						the generic i686 cross-compiler!")
endif()

message(STATUS "Making kernel in directory: " ${CMAKE_SOURCE_DIR})
message(STATUS "C Compiler: '${CMAKE_C_COMPILER}'")
message(STATUS "C++ Compiler: '${CMAKE_CXX_COMPILER}'")
message(STATUS "Compiler flags: '${COMPILER_FLAGS}'")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)

# compile binary under the generic name "myos.bin"
# this name should probably change eventually
# add_executable(kernel_main.o sources/kernel_main.c)

# install(TARGETS PROJECT_NAME DESTINATION isodir/boot)
