#include <stdio.h>
#include "synclib.h"

#define NLOOPS 5

main(){
	int i;
	pid_t pid;
	TELL_WAIT();
	// Fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// Parent process
	else if(pid>0){
		for(i=0;i<NLOOPS;i++){
			// Wake child
			TELL_CHILD();
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n");
			// Wait child
			WAIT_CHILD();
		}
	}
	// Child process
	else{
		for(i=0;i<NLOOPS;i++){
			printf("Child: Wait for parent to tell\n");
			// Wait parent
			WAIT_PARENT();
			// Wake parent
			TELL_PARENT();
			printf("Child: Tell to parent\n");
		}
	}
}
