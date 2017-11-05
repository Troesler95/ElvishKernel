#!/bin/bash
set -e

echo "Running config script..."
source ./config/config.sh

# INSTALL HEADERS
# create the sysdir if it hasn't been created already
mkdir -p "$SYSROOT"

# for each of our projects, install the headers into the appropriate
# place in the sysroot
for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  echo "Installing headers for $PROJECT"
  (cd src/$PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done
