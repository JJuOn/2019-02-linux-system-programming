#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"

main(){
		// Declare variables
		BoundedBufferType	*pBuf;
		int	shmid, i, data;
		int	emptySemid, fullSemid, mutexSemid;
		// Get shared memory
		if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
				perror("shmget");
				exit(1);
		}
		// Attach shared memory
		if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
				perror("shmat");
				exit(1);
		}
		// Initialize semaphores
		if ((emptySemid = semInit(EMPTY_SEM_KEY) ) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((fullSemid = semInit(FULL_SEM_KEY)) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}

		srand(0x8888);
		// Repeat for NLOOPS times
		for (i = 0 ; i < NLOOPS ; i++)  {
				// Wait empty semaphore
				if (semWait(emptySemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				// Wait mutex semaphore
				if (semWait(mutexSemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				// Produce
				printf("Producer: Producing an item.....\n");
				data = (rand()%100)*10000;
				pBuf->buf[pBuf->in].data = data;
				pBuf->in = (pBuf->in + 1) % MAX_BUF;
				pBuf->counter++;
				// Signal mutex semaphore
				if (semPost(mutexSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				// Signal full semaphore
				if (semPost(fullSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				usleep(data);
		}

		printf("Producer: Produced %d items.....\n", i);

		sleep(2);
		printf("Producer: %d items in buffer.....\n", pBuf->counter);
		// Destroy semaphores
		if (semDestroy(emptySemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(fullSemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(mutexSemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		// Delete shared memory
		if (shmctl(shmid, IPC_RMID, 0) < 0)  {
				perror("shmctl");
				exit(1);
		}
}
