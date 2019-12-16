#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "fifo.h"

// Define Signalhandler
int SigIntHandler(int signo){
	char fifoname[256];
	// Set fifoname with format
	sprintf(fifoname,".fifo%d",getpid());
	// Delete fifo
	if(remove(fifoname)<0){
		perror("remove");
		exit(1);
	}
	exit(0);
}
// Main function
main(){
	char fname[MAX_FIFO_NAME];
	int fd,sfd,n;
	MsgType msg;
	// Register signalhandler which deletes fifo file
	signal(SIGINT,SigIntHandler);
	// Set fifoname
	sprintf(fname,".fifo%d",getpid());
	// Make fifo
	if(mkfifo(fname,0600)<0){
		perror("mkfifo");
		exit(1);
	}
	// Open fifo
	if((fd=open(fname,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	// Open Server fifo
	if((sfd=open(SERV_FIFO,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	// Copy fifoname to returnFifo of msg
	strcpy(msg.returnFifo,fname);
	// Set msg.data to which message came from process
	sprintf(msg.data,"This is a request from %d.",getpid());
	// Write msg into server fifo
	write(sfd,(char*)&msg,sizeof(msg));
	printf("Send a request .....");
	// Read my own fifo, if unavailable, wait
	if((n=read(fd,(char*)&msg,sizeof(msg)))<0){
		perror("read");
		exit(1);
	}
	printf("Received reply: %s\n",msg.data);
	// Close fifos
	close(fd);
	close(sfd);
	// Remove fifo
	if(remove(fname)<0){
		perror("remove");
		exit(1);
	}
}
