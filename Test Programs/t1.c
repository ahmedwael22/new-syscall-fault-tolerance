#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <pfork.h>

int main () {
	printf("\nTest 5 Starts\n");
	
	long new_pid = pfork();
	long who_is_this = pfork_who();

	if (who_is_this == 0) {
		wait(NULL);
		wait(NULL);
		printf("\nParent\n");
	}
	if (who_is_this == 1) {
		printf("\nActive Child\n");
		printf("Own PID: %ld\n", new_pid);
		printf("Original Status: %ld\n", get_pfork_status());
		printf("Sibling PID: %d\n", get_pfork_sibling_pid());
		
		set_pfork_status(228);	
		printf("New Status: %ld\n", get_pfork_status());
		
		exit(0);
	}
	if (who_is_this == 2) {
		printf("\nStandby Child\n");
		printf("Own PID: %ld\n", new_pid);
		
		printf("Status: %ld\n", get_pfork_status());
		printf("Sibling PID: %d\n", get_pfork_sibling_pid());
	
		set_pfork_status(999);	
		printf("New Status: %ld\n", get_pfork_status());
		
		exit(0);
	}
	
	printf("Test 5 Ends\n\n");
	return 0;
}
