#!/bin/bash
#############################################
##### Create temp directory for file manipulation
TEMPDIR=.$$
mkdir -p $TEMPDIR/isodir/boot/grub

#############################################
##### Clear temporary files function ########
function quit () {
	rm -R $TEMPDIR
	if [ $1 = succ ]; then
		echo Installation was successful. Your iso file has been placed in the builds directory.
		exit
	else
		echo Installation did not complete successfully. No changes have been made.
		exit
	fi
}

#############################################
##### Compile source files for i686-elf #####

# i686-elf cross-compilers must be installed in PATH
if i686-elf-as ./src/assembly/boot.s -o $TEMPDIR/boot.o; then
	echo Assembly compiled
else
	echo Problem with Assembly files
	quit fail
fi

## This script is designed for kernel written in C

if i686-elf-gcc -c ./src/base/onefile.c -o $TEMPDIR/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra; then
	echo C files compiled
else
	echo Problem with compiling C files
	quit fail
fi

#############################################
##### Link compiled files ###################

if i686-elf-gcc -T ./src/linker.ld -o $TEMPDIR/myos.bin -ffreestanding -O2 -nostdlib $TEMPDIR/boot.o $TEMPDIR/kernel.o -lgcc; then
	echo Linking succeeded
else
	echo Problem with linker files
	quit fail
fi

#############################################
##### Verify multiboot and grub #############

if grub-file --is-x86-multiboot $TEMPDIR/myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot or grub is not installed
  quit fail
fi


#############################################
##### Create iso file structure then create iso #
cp ./$TEMPDIR/myos.bin $TEMPDIR/isodir/boot/myos.bin
cp ./src/grub.cfg $TEMPDIR/isodir/boot/grub/grub.cfg

grub-mkrescue -o builds/newbuild.iso $TEMPDIR/isodir
quit succ