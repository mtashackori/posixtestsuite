# Goal 

this repo targets for supporing POSIX standard better on NetBSD operating system. <br /> 
We started from the posix test benchmark suite http://posixtest.sourceforge.net/ and <br />
did some modifications both in the benchmark side and NetBSD current kernel. <br />

# How to Use This Repo

In terms of benchmark modifications, one can acquire by cloning this repo. <br />
For kernel changes, one can find all patches in the `patch/` folder. <br />
So, at first, apply patches in patch folder to your kernel source tree, then <br />
compiler your kernel, user land and install the new kernel. <br />
Finally, clone this repo, and run `gmake`. From the logs of the benchmark, <br />
one can see the status of each executed test. <br />

# How to Compile Kernel

Because there are too many ways of compiling kernels, the steps of making kernel in this repo is given below. <br />
cp /usr/src/sys/arch/\<arch\>/conf/GENERIC /usr/src/sys/arch/\<arch\>/conf/CURRENT <br />
cd /usr/src <br />
./build.sh -O /usr/current -U -j 8 -u tools kernel=CURRENT modules <br />  
./build.sh -O /usr/current -U -j 8 -u distribution sets <br />
Note: always use -u <br />

# Status

The work is not completed, but you can see the current status from the errors.txt file. <br />
The file works as a roadmap. Missing features in errors.txt will be supported one by one. <br />

# Effectiveness of Each Commit

I have keep a snapshot of the log from the benchmark and keep updating it. <br />
Along with each commit, there will be the changes of the log, then you can see the effectiveness. <br />
Example, git show   23b1580c69b31be95db234913b93b8a11fc4f89e   <br />
