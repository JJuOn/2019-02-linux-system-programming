#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#define SEM_KEY (0x5000+23)

int main(){
	// Declare variables
	int shmid,semid;
	char *ptr,*pData;
	int *pInt;
	// Get shared memory
	if((shmid=shmget(SHM_KEY,SHM_SIZE,SHM_MODE))<0){
		perror("shmget");
		exit(1);
	}
	// Initialize semaphore
	if((semid=semInit(SEM_KEY))<0){
		fprintf(stderr,"semInit failure\n");
		exit(1);
	}
	// Attach shared memory
	if((ptr=shmat(shmid,0,0))==(void*)-1){
		perror("shmat");
		exit(1);
	}
	// Intialize semaphore value
	if(semInitValue(semid,1)<0){
		fprintf(stderr,"semInitValue failiure\n");
		exit(1);
	}
	// Wait semaphore
	if(semWait(semid)<0){
		fprintf(stderr,"semWait failure\n");
		exit(1);
	}
	pInt=(int*)ptr;
	// Write
	pData=ptr+sizeof(int);
	sprintf(pData,"This is a request from %d.",getpid());
	printf("Sent a request.....");
	// Signal semaphore
	if(semPost(semid)<0){
		fprintf(stderr,"semPost failure\n");
		exit(1);
	}
	sleep(1);
	// Wait semaphore
	if(semWait(semid)<0){
		fprintf(stderr,"semWait failure\n");
		exit(1);
	}
	// Read
	printf("Received reply: %s\n",pData);
	// Signal semaphore
	if(semPost(semid)<0){
		fprintf(stderr,"semPost failure\n");
		exit(1);
	}
	// Destroy semaphore
	if(semDestroy(semid)<0){
		fprintf(stderr,"semDestroy failure\n");
		exit(1);
	}
	return 0;
}
