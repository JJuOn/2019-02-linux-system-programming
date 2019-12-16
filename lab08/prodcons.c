#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

// Declare global variables
BoundedBufferType	Buf;
sem_t				EmptySem, FullSem, MutexSem;

// Define thread sleep
void ThreadUsleep(int usecs) {
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

// Define producer
void Producer(void *dummy) {
		int		i, data;

		printf("Producer: Start.....\n");
		// Repeat for NLOOPS times
		for (i = 0 ; i < NLOOPS ; i++)  {
				// Wait empty semaphore
				if (sem_wait(&EmptySem))  {
						perror("sem_wait");
						pthread_exit(NULL);
				}
				// Wait mutex semaphore
				if (sem_wait(&MutexSem))  {
						perror("sem_wait");
						pthread_exit(NULL);
				}
				// Produce
				printf("Producer: Producing an item.....\n");
				data = (rand()%100)*10000;
				Buf.buf[Buf.in].data = data;
				Buf.in = (Buf.in + 1) % MAX_BUF;
				Buf.counter++;
				// Signal mutex semaphore
				if (sem_post(&MutexSem))  {
						perror("sem_post");
						pthread_exit(NULL);
				}
				// Signal full semaphore
				if (sem_post(&FullSem))  {
						perror("sem_post");
						pthread_exit(NULL);
				}
				ThreadUsleep(data);
		}

		printf("Producer: Produced %d items.....\n", i);
		printf("Producer: %d items in buffer.....\n", Buf.counter);

		pthread_exit(NULL);
}

// Define consumer
void Consumer(void *dummy) {
		// Declare variables
		int		i, data;

		printf("Consumer: Start.....\n");
		// Repeat for NLOOPS times
		for (i = 0 ; i < NLOOPS ; i++)  {
				// Wait full semaphore
				if (sem_wait(&FullSem))  {
						perror("sem_wait");
						pthread_exit(NULL);
				}
				// Wait mutex semaphore
				if (sem_wait(&MutexSem))  {
						perror("sem_wait");
						pthread_exit(NULL);
				}
				// Consume
				printf("Consumer: Consuming an item.....\n");
				data = Buf.buf[Buf.out].data;
				Buf.out = (Buf.out + 1) % MAX_BUF;
				Buf.counter--;
				// Signal mutex semaphore
				if (sem_post(&MutexSem))  {
						perror("sem_post");
						pthread_exit(NULL);
				}
				// Signal full semaphore
				if (sem_post(&FullSem))  {
						perror("sem_post");
						pthread_exit(NULL);
				}

				ThreadUsleep((rand()%100)*10000);
		}

		printf("Consumer: Consumed %d items.....\n", i);
		printf("Consumer: %d items in buffer.....\n", Buf.counter);

		pthread_exit(NULL);
}

main()
{
		pthread_t	tid1, tid2;

		srand(0x9999);
		// Initialize semaphores
		if (sem_init(&EmptySem,0,MAX_BUF))  {
				perror("sem_init");
				exit(1);
		}
		if (sem_init(&FullSem,0,0))  {
				perror("sem_init");
				exit(1);
		}
		if (sem_init(&MutexSem,0,0))  {
				perror("sem_init");
				exit(1);
		}
		// Create threads
		if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
				perror("pthread_create");
				exit(1);
		}

		if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
				perror("pthread_create");
				exit(1);
		}
		// Join threads
		if (pthread_join(tid1, NULL) < 0)  {
				perror("pthread_join");
				exit(1);
		}
		if (pthread_join(tid2, NULL) < 0)  {
				perror("pthread_join");
				exit(1);
		}

		printf("Main    : %d items in buffer.....\n", Buf.counter);
		// Destroy semaphores
		if (sem_destroy(&EmptySem))  {
				perror("sem_destroy");
		}
		if (sem_destroy(&FullSem))  {
				perror("sem_destroy");
		}
		if (sem_destroy(&MutexSem))  {
				perror("sem_destroy");
		}
}
