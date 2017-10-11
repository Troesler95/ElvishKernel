project(kernel_base LANGUAGES C CXX)

include_directories(includes)

add_library(kernel_base OBJECT
  src/screen.c
  src/system.c)

set(KERN_BASE_HEADERS includes/screen.h includes/system.h)
