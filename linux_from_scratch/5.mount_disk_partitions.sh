#!/bin/sh

# The loopdevice from losetup is required: (eg: loop0)
if [ $# != 1 ]; then
    echo "Usage: $0 LOOPDEVICE"
    exit
fi

mkdir -p lfs
mount -t ext4 $1p3 lfs
mkdir -p lfs/boot
mount -t ext4 $1p2 lfs/boot

echo 'Run "export LFS=${PWD}/lfs" to set LFS variable'

mkdir -p ${LFS}/tools
ln -s ${LFS}/tools /tools
