#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

int main(){
	int shmid;
	char *ptr,*pData;
	int *pInt;
	// Get shared memory
	if((shmid=shmget(SHM_KEY,SHM_SIZE,SHM_MODE))<0){
		perror("shmget");
		exit(1);
	}
	// Attach shared memory
	if((ptr=shmat(shmid,0,0))==NULL){
		perror("shmat");
		exit(1);
	}
	pInt=(int*)ptr;
	// If first integer of shared memory is 0, busy wait
	while((*pInt)==0);
	pData=ptr+sizeof(int);
	printf("Received request: %s.....",pData);
	// Set pData
	sprintf(pData,"This is a reply from %d.",getpid());
	// Set first integer of shared memeory to 0
	*pInt=0;
	printf("Replied.\n");
	sleep(1);
	// Remove shared memory
	if(shmctl(shmid,IPC_RMID,0)<0){
		perror("shmctl");
		exit(1);
	}
	return 0;
}
