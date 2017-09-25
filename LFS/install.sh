#!/bin/sh -e

if [ "`id -u`" != "0" ]; then
	echo "Script needs root ability" >&2
	exit 1
fi

umask 0022

apt-get update
apt-get upgrade -y
apt-get install -y bash
ln -fs /bin/bash /bin/sh
apt-get install -y binutils binutils-dev
apt-get install -y bison libbison-dev
ln -fs -- "`type -P bison`" /usr/bin/yacc
apt-get install -y bzip2 libbz2-dev
apt-get install -y coreutils
apt-get install -y diffutils
apt-get install -y findutils
apt-get install -y gawk
ln -fs -- "`type -P gawk`" /usr/bin/awk
apt-get install -y g++
apt-get install -y libc6 libc6-dev
# Grep is earlier
apt-get install -y grep
apt-get install -y zlib1g zlib1g-dev
apt-get install -y m4
apt-get install -y make
apt-get install -y patch
# Perl is earlier
apt-get install -y perl
apt-get install -y sed
apt-get install -y tar
apt-get install -y texinfo
apt-get install -y xz-utils

# Partitions
sfdisk < linux.sfdisk

# Format
mke2fs -L '/boot' -t ext4 -v /dev/sdb2
mke2fs -L '/'     -t ext4 -v /dev/sdb4

# Variable LFS
export LFS=/mnt/lfs

# Mount
mkdir -p $LFS
mount -v -t ext4 /dev/sdb4 $LFS
mkdir -p $LFS/boot
mount -v -t ext4 /dev/sdb2 $LFS/boot
mkswap -L swap /dev/sdb3

# Sources
mkdir -v -m 1777 -p $LFS/sources
cd $LFS/sources
wget -nv 'http://www.linuxfromscratch.org/lfs/view/stable-systemd/wget-list'
wget -nv -i wget-list
wget -nv 'http://www.linuxfromscratch.org/lfs/view/stable-systemd/md5sums'
if ! md5sum -c --quiet md5sums ; then
	echo "DOWNLOAD FAILED !"
	exit 1
fi
rm -f -- wget-list md5sums
chmod -- 444 *

# Tools
mkdir -p $LFS/tools
ln -sv $LFS/tools /

# Adduser lfs
useradd -U -s /bin/bash -m -k /dev/null lfs
echo 'lfs:lfs1234' | chpasswd
chown -v lfs $LFS/tools

# Setup lfs user environment
sudo -i -u lfs << "SUDOEOF"
## .bash_profile
cat > ~/.bash_profile << "EOF"
exec env -i HOME=~ TERM=$TERM PS1='\u:\w\$ ' /bin/bash
EOF

## .bashrc
cat > ~/.bashrc << "EOF"
set +h
umask 022
LFS=/mnt/lfs
LC_ALL=POSIX
LFS_TGT=$(uname -m)-lfs-linux-gnu
PATH=/tools/bin:/bin:/usr/bin
export LFS LC_ALL LFS_TGT PATH
alias l='ls -lh --color=auto'
alias ll='l -a'
EOF
SUDOEOF

# Continue script as user lfs
sudo -i -u lfs << "EOF"
source ~/.bashrc
$CHAPTER5/binutils-1.sh
$CHAPTER5/gcc-1.sh
EOF
