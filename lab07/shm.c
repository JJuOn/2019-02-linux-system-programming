#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W)

char Array[ARRAY_SIZE];

int main(){
	int shmid;
	char *ptr,*shmptr;
	// Dynamic allocation of memory
	if((ptr=(char*)malloc(MALLOC_SIZE))==NULL){
		perror("malloc");
		exit(1);
	}
	// Get shared memory id
	if((shmid=shmget(IPC_PRIVATE,SHM_SIZE,SHM_MODE))<0){
		perror("shmget");
		exit(1);
	}
	// Attach shared memory
	if((shmptr=shmat(shmid,0,0))==(void*)-1){
		perror("shmat");
		exit(1);
	}
	// Print informations
	printf("Array[] from %p to %p\n",&Array[0],&Array[ARRAY_SIZE]);
	printf("Stack around %p\n",&shmid);
	printf("Malloced from %p to %p\n",ptr,ptr+MALLOC_SIZE);
	printf("Shared memory attached from %p to %p\n",shmptr,shmptr+SHM_SIZE);
	// Detach shared memory
	if(shmdt(shmptr)<0){
		perror("shmdt");
		exit(1);
	}
	// Remove shared memory
	if(shmctl(shmid,IPC_RMID,0)<0){
		perror("shmctl");
		exit(1);
	}
	return 0;
}
