#!/bin/bash
#############################################
##### Create temp directory for file manipulation
TEMPDIR=$$
mkdir -p $TEMPDIR/isodir/boot/grub

#############################################
##### Compile source files for i686-elf #####

# i686-elf cross-compilers must be installed in PATH
i686-elf-as ./src/assembly/boot.s -o $TEMPDIR/boot.o

# This script is designed for kernel written in C
i686-elf-gcc -c ./src/base/main.c  -o $TEMPDIR/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#############################################
##### Link compiled files ###################

i686-elf-gcc -T ./src/linker.ld -o $TEMPDIR/myos.bin -ffreestanding -O2 -nostdlib $TEMPDIR/boot.o $TEMPDIR/kernel.o -lgcc

#############################################
##### Verify multiboot and grub #############

if grub-file --is-x86-multiboot $TEMPDIR/myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot or grub is not installed
  rm -R ./$TEMPDIR
  echo Installation did not complete. No changes have been made
  exit
fi


#############################################
##### Create iso file structure then create iso #
cp ./$TEMPDIR/myos.bin $TEMPDIR/isodir/boot/myos.bin
cp ./src/grub.cfg $TEMPDIR/isodir/boot/grub/grub.cfg

grub-mkrescue -o builds/myos.iso $TEMPDIR/isodir
rm -R $TEMPDIR
echo File has been created.
exit