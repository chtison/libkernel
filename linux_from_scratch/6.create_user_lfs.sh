#!/bin/sh

useradd -k /dev/null -m -s /bin/bash -U lfs
echo 'lfs:lfs1234' | chpasswd

chown -v lfs $LFS/tools
mkdir -p $LFS/sources
chown -v lfs $LFS/sources

echo 'Run "export LFS=${PWD}/lfs" to set LFS variable'

su - lfs
