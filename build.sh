#!/bin/bash
set -e

echo "Installing headers..."
# first, build the headers
. ./config/headers.sh

# install each of the projects in the system root
# in the appropriate place!
for PROJECT in $PROJECTS; do
  echo "Making $PROJECT..."
  (cd "src/$PROJECT" && DESTDIR="$SYSROOT" $MAKE install)
done
