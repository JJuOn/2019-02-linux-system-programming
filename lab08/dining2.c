#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#define	NUM_MEN		5
#define	NLOOPS		5

#define	LEFT(i)		((i+NUM_MEN-1)%NUM_MEN)
#define	RIGHT(i)	((i+1)%NUM_MEN)

// Define global variables
enum  { THINKING, EATING, HUNGRY };

sem_t Philosopher[NUM_MEN];
sem_t Mutex;
int	State[NUM_MEN];

// Define thread sleep library
void ThreadUsleep(int usecs){
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

// Define thinking
void Thinking(int id){
	// Print and sleep and print
	printf("Philosopher%d: Thinking.....\n", id);
	ThreadUsleep((rand()%200)*10000);
	printf("Philosopher%d: Want to eat.....\n", id);
}

// Define eating
void Eating(int id){
	// Print and sleep
	printf("Philosopher%d: Eating.....\n", id);
	ThreadUsleep((rand()%100)*10000);
}

// Define test
void Test(int id) {
	// If i'm hungry and left and right philosopher aren't eating,
	if (State[id] == HUNGRY && State[LEFT(id)] != EATING && State[RIGHT(id)] != EATING)  {
		// Change my status
		State[id] = EATING;
		// Signal philosohper[id]
		if (sem_post(&Philosopher[id])<0)  {
			perror("sem_post");
			pthread_exit(NULL);
		}
	}
}

// Define PickUp
void PickUp(int id){
	// Wait mutex
	if (sem_wait(&Mutex)<0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	// Change my status
	State[id] = HUNGRY;
	// Do Test
	Test(id);
	// Signal mutex
	if (sem_post(&Mutex)<0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}
	// Wait philosopher[id]
	if (sem_wait(&Philosopher[id])<0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
}

// Define PutDown
void PutDown(int id){
	// Wait mutex
	if (sem_wait(&Mutex)<0)  {
		perror("sem_wait");
		pthread_exit(NULL);
	}
	// Change my status
	State[id] = THINKING;
	// Test left philosopher and rigt philosopher
	Test(LEFT(id));
	Test(RIGHT(id));
	// Singal mutex
	if (sem_post(&Mutex)<0)  {
		perror("sem_post");
		pthread_exit(NULL);
	}
}

// Define DiningPhilosopher
void DiningPhilosopher(int *pId){
	int	i;
	int	id = *pId;
	// For nloops, repeat the below sequence
	for (i = 0 ; i < NLOOPS ; i++)  {
		Thinking(id);
		PickUp(id);
		Eating(id);
		PutDown(id);
	}
	printf("Philosopher%d: thinking & eating %d times.....\n", id, i);
	pthread_exit(NULL);
}

main(){
	pthread_t tid[NUM_MEN];
	int	i, id[NUM_MEN];
	srand(0x8888);
	// Initialize semaphores and id[]
	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_init(&Philosopher[i],0,0)<0)  {
				perror("sem_init");
				exit(1);
		}
		id[i] = i;
	}
	// Initialize mutex semaphore
	if (sem_init(&Mutex,0,1)<0)  {
		perror("sem_init");
		exit(1);
	}
	// Create threads
	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_create(&tid[i], NULL, (void *)DiningPhilosopher, (void *)&id[i]) < 0)  {
			perror("pthread_create");
			exit(1);
		}
	}
	// Join threads
	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_join(tid[i], NULL) < 0)  {
			perror("pthread_join");
			exit(1);
		}
	}
	// Destroy semaphores
	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_destroy(&Philosopher[i])<0)  {
			perror("sem_destroy");
		}
	}
	// Destory mutex semaphore
	if (sem_destroy(&Mutex)<0)  {
		perror("sem_destroy");
		exit(1);
	}

}
