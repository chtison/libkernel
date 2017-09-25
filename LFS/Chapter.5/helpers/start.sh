#!/bin/sh -ex

if [ $# != 4 ]; then
	echo "Usage: $0 TARFILE EXTRACTED_DIR FUNCTION RM"
fi

pushd $LFS/sources
tar xf $1
cd $2

$3

if [ "$4" != "false" ]; then
	$4 $2
fi
popd
