#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

char msg[100];

sem_t Sem,Readable;

void
ThreadUsleep(int usecs)
{
		pthread_cond_t		cond;
		pthread_mutex_t		mutex;
		struct timespec		ts;
		struct timeval		tv;

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

void Writer(){
	if(sem_wait(&Sem)<0){
		perror("sem_wait");
		pthread_exit(NULL);
	}
	strcpy(msg,"Hello");
	if(sem_post(&Sem)<0){
		perror("sem_post");
		pthread_exit(NULL);
	}
	if(sem_post(&Readable)<0){
		perror("sem_post");
		pthread_exit(NULL);
	}
	ThreadUsleep(1000);
}

void Reader(){
	if(sem_wait(&Readable)<0){
		perror("sem_wait");
		pthread_exit(NULL);
	}
	if(sem_wait(&Sem)<0){
		perror("sem_wait");
		pthread_exit(NULL);
	}
	printf("msg: %s\n",msg);
	if(sem_post(&Sem)<0){
		perror("sem_post");
		pthread_exit(NULL);
	}
	ThreadUsleep(1000);
}

int main(){
	pthread_t tid1,tid2;
	if(sem_init(&Sem,0,1)<0){
		perror("sem_init");
		exit(1);
	}
	if(sem_init(&Readable,0,0)<0){
		perror("sem_init");
		exit(1);
	}
	if(pthread_create(&tid1,NULL,Writer,NULL)<0){
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&tid2,NULL,Reader,NULL)<0){
		perror("pthread_create");
		exit(1);
	}
	if(pthread_join(tid1,NULL)<0){
		perror("pthread_join");
		exit(1);
	}
	if(pthread_join(tid2,NULL)<0){
		perror("pthread_join");
		exit(1);
	}
	if(sem_destroy(&Sem)<0){
		perror("sem_destroy");
	}
	return 0;
}
