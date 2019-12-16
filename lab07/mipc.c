#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "synclib.h"

#define NLOOPS 10
#define SIZE sizeof(long)
// Define update function
int update(long *ptr){
	return ((*ptr)++);
}

int main(){
	int fd,i,counter;
	pid_t pid;
	caddr_t area;
	// Open zero file which always returns 0
	if((fd=open("/dev/zero",O_RDWR))<0){
		perror("open");
		exit(1);
	}
	// Map physical memory to virtual memory
	if((area=mmap(0,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0))==(caddr_t)-1){
		perror("mmap");
		exit(1);
	}
	// Close zero file
	close(fd);
	TELL_WAIT();
	// Fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// If parent process
	else if(pid>0){
		for(i=0;i<NLOOPS;i+=2){
			// Update counter
			if((counter=update((long*)area))!=i){
				fprintf(stderr,"Counter mismatch\n");
				exit(1);
			}
			printf("Parent: counter=%d\n",counter);
			// Wake child
			TELL_CHILD();
			// Wait child
			WAIT_CHILD();
		}
	}
	// If child process
	else{
		for(i=1;i<NLOOPS;i+=2){
			// Wait parent
			WAIT_PARENT();
			// Update counter
			if((counter=update((long*)area))!=i){
				fprintf(stderr,"Counter mismatch\n");
				exit(1);
			}
			printf("Child: counter=%d\n",counter);
			// Wake parent
			TELL_PARENT();
		}
	}
	return 0;
}
