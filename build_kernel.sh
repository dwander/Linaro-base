#!/bin/bash

export ARCH=arm64
export CROSS_COMPILE=../PLATFORM/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
#export CROSS_COMPILE=./tools/prebuilts/gcc-cfp-jopp-only/aarch64-linux-android-4.9/bin/aarch64-linux-android-
#export PATH=$(pwd)/./tools/prebuilts/gcc-cfp-jopp-only/aarch64-linux-android-4.9/bin:$PATH

make exynos8890-gracelte_defconfig
make -j64
