#!/bin/sh -e

mkdir -p $LFS
mount -v -t ext4 /dev/sdb4 $LFS
mkdir -p $LFS/boot
mount -v -t ext4 /dev/sdb2 $LFS/boot
mkswap -L swap /dev/sdb3
