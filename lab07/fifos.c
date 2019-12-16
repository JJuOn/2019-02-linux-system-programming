#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"

// Singal handler, which deletes server fifo
void SigIntHandler(int signo){
	if(remove(SERV_FIFO)<0){
		perror("remove");
		exit(1);
	}
	exit(0);
}

main(){
	int fd,cfd,n; 
	MsgType msg;
	// Register signal handler
	if(signal(SIGINT,SigIntHandler)==SIG_ERR){
		perror("signal");
		exit(1);
	}
	// Make server fifo
	if(mkfifo(SERV_FIFO,0600)<0){
		if(errno!=EEXIST){
			perror("mkfifo");
			exit(1);
		}
	}
	// Open server fifo
	if((fd=open(SERV_FIFO,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	while(1){
		// Read server fifo, if unavailable, wait
		if((n=read(fd,(char*)&msg,sizeof(msg)))<0){
			// If an error occurred by signal, continue
			if(errno==EINTR){
				continue;
			}
			else{
				perror("read");
				exit(1);
			}
		}
		printf("Received request: %s.....",msg.data);
		// Open client fifo by using returnFifo of msg
		if((cfd=open(msg.returnFifo,O_WRONLY))<0){
			perror("open");
			exit(1);
		}
		// Write msg into clinet fifo
		sprintf(msg.data,"This is a reply from %d.",getpid());
		write(cfd,(char*)&msg,sizeof(msg));
		// Close client fifo
		close(cfd);
		printf("Replied.\n");
	}
}
