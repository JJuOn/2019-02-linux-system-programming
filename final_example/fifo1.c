#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

typedef struct{
	char data[20];
} Msg;

void SigIntHandler(int signo){
	if(remove("./.myfifo")<0){
		perror("remove");
		exit(1);
	}
	exit(0);
}

main(){
	int fd,n;
	Msg message;
	if(signal(SIGINT,SigIntHandler)==SIG_ERR){
		perror("signal");
		exit(1);
	}
	if(mkfifo("./.myfifo",0600)<0){
		if(errno!=EEXIST){
			perror("mkfifo");
			exit(1);
		}
	}
	if((fd=open("./.myfifo",O_RDWR)) < 0){
		perror("open");
		exit(1);
	}
	printf("Start to Read\n");
	if((n=read(fd,&message,sizeof(message)))<0){
		perror("read");
		exit(1);
	}
	printf("FIFO1: Received a message: %s\n",message.data);
	close(fd);
	sleep(1);
	if((fd=open("./.myfifo",O_RDWR))<0){
		perror("open");
		exit(1);
	}
	strcpy(message.data,"Hi");
	write(fd,&message,sizeof(message));
	printf("FIFO1: Sent a message: %s\n",message.data);
	close(fd);
}
