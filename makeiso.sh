#!/bin/sh
#############################################
##### Create temp directory for file manipulation
TEMPDIR=$$
mkdir -p $TEMPDIR/isodir/boot/grub

#############################################
##### Verify multiboot and grub #############

if grub-file --is-x86-multiboot kroot/boot/myos.kernel; then
  echo multiboot confirmed
else
  echo the file is not multiboot or grub is not installed
  rm -R ./$TEMPDIR
  echo Installation did not complete. No changes have been made
  exit
fi

#############################################
##### Create iso file structure then create iso #
cp kroot/boot/myos.kernel $TEMPDIR/isodir/boot/myos.kernel

cat > $TEMPDIR/isodir/boot/grub/grub.cfg << EOF
menuentry "myos" {
	multiboot /boot/myos.kernel
}
EOF

grub-mkrescue -o builds/myos.iso $TEMPDIR/isodir
rm -R $TEMPDIR
echo File has been created.
exit
