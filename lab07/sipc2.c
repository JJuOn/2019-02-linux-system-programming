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
	if((ptr=shmat(shmid,0,0))==(void*)-1){
		perror("shmat");
		exit(1);
	}
	pInt=(int*)ptr;
	pData=ptr+sizeof(int);
	// Write data to shared memory
	sprintf(pData,"This is a request from %d.",getpid());
	*pInt=1;
	printf("Sent a request.....");
	// If first integer is 1, busy wait
	while((*pInt)==1);
	printf("Received reply: %s\n",pData);
	return 0;
}
