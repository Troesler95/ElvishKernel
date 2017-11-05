#!/bin/sh
set -e

. ./config/config.sh

for PROJECT in $PROJECTS; do
	(cd src/$PROJECT && $MAKE clean)
done

echo "Removing kroot..."
rm -rf kroot
echo "Done."
