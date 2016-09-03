# Goal 

this repo targets for supporing POSIX standard better on NetBSD operating system. <br /> 
We started from the posix test benchmark suite http://posixtest.sourceforge.net/ and <br />
did some modifications both in the benchmark side and NetBSD current kernel. <br />

# How to Use This Repo

In terms of benchmark modifications, one can acquire by cloning this repo or find patch in `patch/TESTSUITE`. <br />
For NetBSD related changes, one can find all patches in the `patch/` folder. <br />
This folder is organized by features. Each subfolder may have `OLD/` folder, <br />
which usually implements the feature in a different way, but not used finally. <br />
So, at first, apply patches in `patch/` folder to your kernel source tree, then <br />
compiler your kernel, user land and install the new kernel. <br />
Finally, clone this repo, and run `gmake`. From the logs of the benchmark, <br />
one can see the status of each executed test. <br />

# How to Compile Kernel

Because there are too many ways of compiling kernels, the steps of making kernel in this repo is given below. <br />
`cp /usr/src/sys/arch/<arch>/conf/GENERIC /usr/src/sys/arch/<arch>/conf/CURRENT` <br />
`cd /usr/src` <br />
`./build.sh -O /usr/current -U -j 8 -u tools kernel=CURRENT modules` 	Note: always use -u <br />
`./build.sh -O /usr/current -U -j 8 -u distribution sets` <br />
`cp /usr/current/sys/arch/<arch>/compile/CURRENT/netbsd /` <br />
`cd /usr/src` <br />
`./build.sh -U -O /usr/current install=/` <br />

# Status

The work is not completed, but you can see the current status from the errors.txt file. <br />
The file works as a roadmap. Missing features in errors.txt will be supported one by one. <br />

# Effectiveness of Each Commit

I have keep a snapshot of the log from the benchmark and keep updating it. <br />
Along with each commit, there will be the changes of the log, then you can see the effectiveness. <br />
Example, git show   23b1580c69b31be95db234913b93b8a11fc4f89e   <br />

# Impact

Following changes (both kernel and userland) have been accepted into NetBSD source tree. <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/b9650369701dd2c95c6f6afa589b1be6bcedbe58 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/203128993a0d31b47978fa659f8ae456bbed5a1c <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/272d39e2405b0c730cbcf300cf4879220a967aa7 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/b6c4d4ba3de2aed35ceba10f027225a04ca697a3 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/80dec21a89c7d0033ce1f54846cbfc7d675656a6 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/8312e2efc6d0a9e03b8774bb9fcd5aac3d73907a <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/053c58f1df1ccb730a2973d5690003c01b1182e1 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/2b763ded396e6526d1cc63b89acd558e6de63f32 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/ef38d5736b7367bff9aba260f532e5b24728b224 <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/6d66b56857eaf348825503072b60948bc3117c4e <br />
https://github.com/IIJ-NetBSD/netbsd-src/commit/7bfee8739f8b88a7eceb5dfe52fce3213fb009a8 <br />

The patch for the POSIX test suite is send to the community also. <br />
https://github.com/ycui1984/posixtestsuite/tree/master/patches/TESTSUITE <br />
