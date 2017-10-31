#!/bin/sh

dd if=/dev/zero of=disk.img bs=$((2**20)) count=$((2**10*20))
