#!/bin/bash -ex

BINUTILS='binutils-2.29'


function binutils-1() {
	mkdir -pv build
	cd build
	../configure --prefix=/tools            \
	             --with-sysroot=$LFS        \
	             --with-lib-path=/tools/lib \
	             --target=$LFS_TGT          \
	             --disable-nls              \
	             --disable-werror

	make

	case $(uname -m) in
	  x86_64) mkdir -v /tools/lib && ln -sv lib /tools/lib64 ;;
	esac

	make install
}
