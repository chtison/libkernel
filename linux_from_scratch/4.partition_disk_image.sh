#!/bin/sh

# The loopdevice from losetup is required: (eg: loop0)
if [ $# != 1 ]; then
    echo "Usage: $0 LOOPDEVICE"
    exit
fi

mke2fs -t ext4 $1p2
mke2fs -t ext4 $1p3
