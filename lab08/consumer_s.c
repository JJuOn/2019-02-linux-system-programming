#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"

main()
{
		// Define variables
		BoundedBufferType	*pBuf;
		int					shmid, i, data;
		int					emptySemid, fullSemid, mutexSemid;
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
		// Initiate semaphores
		if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0)  {
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
		// Set semaphores's value
		if (semInitValue(emptySemid,MAX_BUF) < 0)  {
				fprintf(stderr, "semInitValue failure\n");
				exit(1);
		}
		if (semInitValue(fullSemid,0) < 0)  {
				fprintf(stderr, "semInitValue failure\n");
				exit(1);
		}
		if (semInitValue(mutexSemid,1) < 0)  {
				fprintf(stderr, "semInitValue failure\n");
				exit(1);
		}

		srand(0x9999);
		for (i = 0 ; i < NLOOPS ; i++)  {
				// Wait full semaphore
				if (semWait(fullSemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				// Wait mutex semaphore
				if (semWait(mutexSemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				// Consume
				printf("Consumer: Consuming an item.....\n");
				data = pBuf->buf[pBuf->out].data;
				pBuf->out = (pBuf->out + 1) % MAX_BUF;
				pBuf->counter--;
				// Signal mutex semaphore
				if (semPost(mutexSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				// Signal empty semaphore
				if (semPost(emptySemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}

				usleep((rand()%100)*10000);
		}

		printf("Consumer: Consumed %d items.....\n", i);
		printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
