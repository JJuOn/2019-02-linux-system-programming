#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include "synclib.h"
#include "shm.h"

#define NLOOPS 10
#define SIZE sizeof(long)
// Update pointer
int update(long *ptr){
	return ((*ptr)++);
}

int main(){
	int fd,i,counter,shmid,*ptr,*pInt,*pData;
	pid_t pid;
	// Get shared memory
	if((shmid=shmget(SHM_KEY,SHM_SIZE,SHM_MODE))<0){
		perror("open");
		exit(1);
	}
	// Attach shared memory
	if((ptr=shmat(shmid,0,0))==(void*)-1){
		perror("shmat");
		exit(1);
	}
	TELL_WAIT();
	pInt=(int*)ptr;
	pData=ptr+sizeof(int);
	// Fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// Parent process
	else if(pid>0){
		// For 0 and even number
		for(i=0;i<NLOOPS;i+=2){
			// Update counter
			if((counter=update((long*)pData))!=i){
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
	// Child process
	else{
		// For odd number
		for(i=1;i<NLOOPS;i+=2){
			// Wake parent
			WAIT_PARENT();
			// Update counter
			if((counter=update((long*)pData))!=i){
				fprintf(stderr,"Counter mismatch\n");
				exit(1);
			}
			printf("Child: counter=%d\n",counter);
			// Wake parent
			TELL_PARENT();
		}
		// Delete shared memory
		if(shmctl(shmid,IPC_RMID,0)<0){
			perror("shmctl");
			exit(1);
		}
	}
	return 0;
}
