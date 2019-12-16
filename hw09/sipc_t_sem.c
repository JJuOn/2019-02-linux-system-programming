#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include "shm.h"

// Declare global variable
int Flag=0,Data;
sem_t Sem;

// Define thread sleep
void ThreadUsleep(int usecs) {
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	struct timespec ts;
	struct timeval tv;
	if (pthread_cond_init(&cond, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}
	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}
	if (pthread_mutex_lock(&mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}
	if (pthread_cond_destroy(&cond) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}

// Define thread handler
void ThreadHandler(pthread_t tid){
	int i;
	for(i=0;i<10;i++){
		// Wait semaphore
		if(sem_wait(&Sem)<0){
			perror("sem_wait");
			pthread_exit(1);
		}
		// Read data
		printf("Read tid: %d, Data: %d\n",tid,Data);
		// Write data
		Data=rand()%100;
		printf("Write tid: %d, Data: %d\n",tid,Data);
		// Signal semaphore
		if(sem_post(&Sem)<0){
			perror("sem_post");
			pthread_exit(1);
		}
		ThreadUsleep(Data*10000);
	}
}

int main(){
	// Declare variables
	pthread_t tid1,tid2;
	srand(0);
	// Initialize data
	Data=rand()%100;
	// Initialzie semaphore
	if(sem_init(&Sem,0,1)<0){
		perror("sem_init");
		exit(1);
	}
	// Create threads
	if(pthread_create(&tid1,NULL,(void*)ThreadHandler,&tid1)<0){
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&tid2,NULL,(void*)ThreadHandler,&tid2)<0){
		perror("pthread_create");
		exit(1);
	}
	// Join threads
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	// Destroy semaphore
	if(sem_destroy(&Sem)<0){
		perror("sem_destroy");
		exit(1);
	}
	return 0;
}
