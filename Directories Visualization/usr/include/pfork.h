/* Ahmed Wael Change New */
/* Entire File is newly created by me */

#include <stdio.h>
#include <x86_64-linux-gnu/sys/types.h>

long int pfork() {
	return syscall(440);
}

long set_pfork_status(long status_provided) {
	return syscall(441, status_provided);
}

long get_pfork_status() {
	return syscall(442);
}

pid_t get_pfork_sibling_pid() {
	return syscall(443);
}

long pfork_who() {
	return syscall(444);
}
