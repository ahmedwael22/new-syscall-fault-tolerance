# new-syscall-fault-tolerance
Modified the Linux kernel by creating a new syscall to allow for process fault tolerance

## Directory Structure
This readme file explains the structure of the Submitted Zip File.





There is a folder called "Patches".
This folder contains the patches obtained by using the diff command to compare the original files with the versions I modified.
There are six files in this folder.

1) patch_fork.txt
2) patch_exit.txt
3) patch_sched
4) patch_pfork_userside_library
5) patch_syscall_64_tbl
6) patch_syscalls_h

Files 1 and 2 refer to patches of files found inside /linux/kernel.
The two original files are fork.c and exit.c.
I modified these two files, and you can find the modifications in the patch files.
The modifications for fork.c include the introduction of 5 syscalls and a helper function called _do_pfork,
	and adding a few extra lines of code to the helper function copy_process.
The modifications for exit.c include changing the function called do_group_exit.

File 3 refers to a patch of a file found in /linux/include/linux.
The original file is sched.h.
I modified this file to include 4 new fields in the struct task_struct (3 required by the Exercise and 1 more which I explain in the file).

File 4 refers to a patch of a COMPLETELY NEW file.
This file should reside under /usr/include.
This file is called pfork.h
This is creates a user-side library that contains functions that wrap the new syscalls.
I decided to create just one file (.h) instead of two files (.h and .c), to maintain consistency set by the files in the directory itself,
	and because it was much simpler (because the wrappers were very direct and straightforward).

File 5 refers to a patch of a file found in /linux/arch/x86/entry/syscalls
The original file is syscall_64.tbl
I modified this file to include the five new syscalls, numbered from 440 to 444
	(because 440 was the first unused and eligible syscall number)
The second column has entries common becuase the syscall is supported by both 64-bit and 32-bit architectures.
The fourth column contains the sys_ prefix as per Linux requirements.

File 6 refers to a patch of a file found in /linux/include/linux
The original file is syscalls.h
I modified this to include asmlinkage for the five new syscalls, with their defined return types and any parameters they receive.




The directory called "New and Modified Files" contains the actual files I mention above.
Instead of just providing you with patches, I have given you the complete files after modifications.




The directory called "Old Files (Unmodified)" contains the files in their UNEDITED format.
These files are NOT INTENDED for any practical usage, and they should only be used in comparison to the new files I have also provided.




The directory called "Directories Visualization" is intended to simualte or visualize the structure and hierarchy of the files.
Pretend that "Directories Visualization" corresponds to the root directory.
Inside that, we have two directories: linux and usr.
	"linux" directory: contains directories "kernel", "include", and "arch".
		"kernel": contains "fork.c" and "exit.c"
		"include": contains another directory "linux",
			which contains "sched.h" and "syscalls.h"
		"arch": contains another directory "x86"
			"x86": contains another directory "entry"
				"entry": contains another directory "syscalls"
					"syscalls": contains "syscall_64.tbl"
	"usr" directory: contains another directory "include"
		"include": contains pfork.h (the user-side library that has the wrappers for the syscalls)

Note that there are essentially just six files in the "Directries Visualization" folder,
	which are fork.c, exit.c, sched.h, syscalls.h, syscall_64.tbl, and pfork.h
These are the same files found in the directory "New and Modified Files",
	but they are just arranged differently, to show how they should be arranged in an environment that needs to use the pfork and helpers.
	This is the arrangement on my Virtual Machine, and it works correctly.




The directory "Test Programs" contains two .c files (t1.c and dr_test.c) and 1 Makefile.
The contents of this directory are used to test my pfork syscall and the helper syscalls.
	t1.c is a program I created that tests all 5 syscalls;
	dr_test.c is another program that less thoroughly tests the syscalls.

To run a test do the following:
	Make sure that your kernel is compiled with MY new versions of pfork.c, exit.c, sched.h, syscalls.h, syscall_64.tbl
		in their CORRECT directories (as illustrated in "Directories Visualization")
	Make sure that pfork.h is placed in its CORRECT directory (as illustrated in "Directories Visualization")
	Open terminal from the Test Programs directory
	Run the command:
		make all
	To test t1.c (whose executable output is called e1), run the command:
		./e1
	To test dr_test.c (whose executable output is called r1), run the command:
		./r1
	To remove the exectuables after testing them, run the command:
		make clean
