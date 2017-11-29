DEFAULT_HOST!=$(../../config/./default_target.sh)
HOST?=DEFAULT_HOST

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

ASM_DIR:=assembly

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS)-nostdlib -lk -lgcc

CRTI_OBJ:=crti.o
CRTN_OBJ:=crtn.o

CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

KERNEL_OBJS:=\
src/screen.o \
src/system.o \
main.o \

OBJS:=\
$(ASM_DIR)/crti.o \
$(ASM_DIR)/crtbegin.o \
$(ASM_DIR)/boot.o \
$(KERNEL_OBJS) \
$(ASM_DIR)/crtend.o \
$(ASM_DIR)/crtn.o \

LINK_LIST:=\
$(LDFLAGS) \
$(ASM_DIR)/crti.o \
$(ASM_DIR)/crtbegin.o \
$(ASM_DIR)/boot.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ASM_DIR)/crtend.o \
$(ASM_DIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: myos.kernel

myos.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot myos.kernel

$(ASM_DIR)/crtbegin.o $(ASM_DIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu99 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: myos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp myos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
