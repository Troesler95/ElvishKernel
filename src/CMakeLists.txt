project(kernel_main LANGUAGES C CXX)

add_subdirectory(kernel_base)

# compile kernel executable w/ kernel_base library
add_library(kernel.o STATIC $<TARGET_OBJECTS:kernel_base>
kernel_main.c ${KERN_BASE_HEADERS})

target_include_directories( kernel.o PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/kernel_base/includes>
  $<INSTALL_INTERFACE:kernel_base/includes>
  PRIVATE kernel_base
)


# compile assembly code to be later lined with linker code
enable_language(ASM-ATT)
add_library(boot.o OBJECT tutorial_boot.s)

add_executable(myos.bin kernel.o boot.o)
set_target_properties(myos.bin PROPERTIES LINK_DEPENDS tutorial_linker.ld)
