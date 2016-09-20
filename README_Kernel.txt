################################################################################

1. How to Build
	- get Toolchain
		From android git server , codesourcery and etc ..
		
	- edit Makefile
			edit "CROSS_COMPILE" to right toolchain path(You downloaded).
			Ex)  CROSS_COMPILE=/opt/toolchains/arm-eabi-4.8/bin/arm-eabi-                 // You have to check.

	- make
			$ cd kernel
			$ make ARCH=arm exynos5433-trelteskt_defconfig
			$ make ARCH=arm

2. Output files
	- Kernel : arch/arm/boot/zImage
	- module : drivers/*/*.ko

3. How to Clean	
		$ make clean
################################################################################
