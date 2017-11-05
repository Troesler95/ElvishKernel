# define the host to compile to
DEFAULT_HOST!=../../config/default_target.sh
HOST?=DEFAULT_HOST
HOSTARCH!=echo i386 $(HOST)

# on the off chance these vars haven't been set yet, set them
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

# set the directories to install into
# if not previously set
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX=?$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

# add additional flags for compiling freestanding code
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -fpic
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

# architecture specific flags would go here
# we don't have to worry about this for now, but if we do
# reference http://wiki.osdev.org/Meaty_Skeleton for the structure

# This would allow us to build host-specific builds
# for right now, it will go unused
#
# all the object files (one for each source files) should
# be listed below!
# If you add a new source DONT FORGET TO ADD IT TO THIS LIST
FREEOBJS=\
string.o \

HOSTEDOBJS=\

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

# name of the binary to produce
BINARIES=libk.a

# define the operations this file will support
.PHONY: all clean install install-headers install-libs
# define the files we will be looking for
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

# add all the objects to a library archive
libc.a: $(OBJS)
				$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
				$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
			$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.c.S:
				$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
				$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
				$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
				rm -f $(BINARIES) *.a
				rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
				rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
				mkdir -p $(DESTDIR)$(INCLUDEDIR)
				cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
				mkdir -p $(DESTDIR)$(LIBDIR)
				cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
