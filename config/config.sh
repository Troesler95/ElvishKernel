#!/bin/bash

# defines the projects that need to be built
# in order or prescedence
# i.e. the library needs to be built before base!
SYSTEM_HEADER_PROJECTS="lib base"
PROJECTS="lib base"

# define make, define host to be i686-elf
export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./config/default_target.sh)}

# override compilers to be the cross-compiler
export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc
echo $CC

# define standard places to store our libs, headers, etc..
export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'

# define a root for our system to look into to resolve
# dependencies
export SYSROOT="$(pwd)/kroot"
export CC="$CC --sysroot=$SYSROOT"

# When using the i686-elf compiler,
# we need to tell it where to look for system headers
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
