#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "semlib.h"
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
	if((ptr=shmat(shmid,0,0))==NULL){
		perror("shmat");
		exit(1);
	}
	pInt=(int*)ptr;
	// Wait semaphore
	if(semWait(semid)<0){
		fprintf(stderr,"semWait failure\n");
		exit(1);
	}
	// Write data
	pData=ptr+sizeof(int);
	printf("Received request: %s.....",pData);
	sprintf(pData,"This is a reply from %d.",getpid());
	// Signal semaphore
	if(semPost(semid)<0){
		fprintf(stderr,"semPost failure\n");
		exit(1);
	}
	printf("Replied.\n");
	sleep(1);
	// Delete shared memory
	if(shmctl(shmid,IPC_RMID,0)<0){
		perror("shmctl");
		exit(1);
	}
	return 0;
}
