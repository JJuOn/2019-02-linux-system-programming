#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"


main()
{
		// Define variables
		BoundedBufferType *pBuf;
		int	shmid, i, data;
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
		// Set up random seed
		srand(0x9999);
		for (i = 0 ; i < NLOOPS ; i++)  {
				// If buffer is empty, busy waiting
				if (pBuf->counter == 0)  {
						printf("Consumer: Buffer empty. Waiting.....\n");
						while (pBuf->counter == 0)
								;
				}
				// Consume the item
				printf("Consumer: Consuming an item.....\n");
				data = pBuf->buf[pBuf->out].data;
				pBuf->out = (pBuf->out + 1) % MAX_BUF;
				pBuf->counter--;

				usleep((rand()%100)*10000);
		}

		printf("Consumer: Consumed %d items.....\n", i);
		printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
