#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include "shm.h"

// Declare variables
int Flag=0,Data;
pthread_mutex_t Mutex;
pthread_cond_t Cond;

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
		// Lock
		if(pthread_mutex_lock(&Mutex)<0){
			perror("phtread_mutex_lock");
			exit(1);
		}
		// If flag is 1, it means another thread using data
		while(Flag==1){
			printf("tid %d is waiting...\n",tid);
			if(pthread_cond_wait(&Cond,&Mutex)<0){
				perror("pthread_cond_wait");
				exit(1);
			}
		}
		Flag=1;
		// Read data
		printf("Read tid: %d, Data: %d\n",tid,Data);
		// Write data
		Data=rand()%100;
		printf("Write tid: %d, Data: %d\n",tid,Data);
		Flag=0;
		// Signal condition variable
		if(pthread_cond_signal(&Cond)<0){
			perror("pthread_cond_signal");
			exit(1);
		}
		// Unlock
		if(pthread_mutex_unlock(&Mutex)<0){
			perror("pthread_mutex_unlock");
			exit(1);
		}
		ThreadUsleep(Data*10000);
	}
}

int main(){
	// Declare variables
	pthread_t tid1,tid2;
	srand(0);
	Data=rand()%100;
	// Initialize mutex
	if(pthread_mutex_init(&Mutex,NULL)<0){
		perror("pthread_mutex_init");
		exit(1);
	}
	// Initialize condition variable
	if(pthread_cond_init(&Cond,NULL)<0){
		perror("pthread_cond_init");
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
	// Destroy mutex
	pthread_mutex_destroy(&Mutex);
	// Destroy condition variable
	pthread_cond_destroy(&Cond);
	return 0;
}
