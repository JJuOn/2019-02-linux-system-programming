#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include "tcp.h"
#include <sys/time.h>
#include <string.h>

int Sockfd;

typedef struct {
	int type;
	char clientId[100];
} MsgType;

void CloseServer(){
	close(Sockfd);
	printf("\nTCP Server exit.....\n");
	exit(0);
}

main(){
	int pid,newSockfd,cliAddrLen,n;
	struct sockaddr_in cliAddr,servAddr;
	struct timeval tv;
	struct timezone tz;
	MsgType msg;
	signal(SIGINT,CloseServer);
	if((Sockfd=socket(PF_INET,SOCK_STREAM,0))<0){
		perror("socket");
		exit(1);
	}

	bzero((char*)&servAddr,sizeof(servAddr));
	servAddr.sin_family=PF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(SERV_TCP_PORT);
	if(bind(Sockfd,(struct sockaddr *)&servAddr,sizeof(servAddr))<0){
		perror("bind");
		exit(1);
	}
	listen(Sockfd,5);
	printf("TCP Server started.....\n");
	cliAddrLen=sizeof(cliAddr);
	while(1){
		newSockfd=accept(Sockfd,(struct sockaddr*)&cliAddr,&cliAddrLen);
		if((pid=fork())<0){
			perror("fork");
			exit(1);
		}
		else if(pid==0){
			if(newSockfd<0){
				perror("accept");
				exit(1);
			}
			if((n=read(newSockfd,&msg,sizeof(msg)))<0){
				perror("read");
				exit(1);
			}
			int logFd;
			if((logFd=open(msg.clientId,O_CREAT|O_RDWR|O_APPEND,0777))<0){
				perror("open");
				exit(1);
			}
			if(gettimeofday(&tv,&tz)<0){
				perror("gettimeofday");
				exit(1);
			}
			char log[20];
			sprintf(log,"%ld\n",tv.tv_sec);
			if(write(logFd,(char*)log,strlen(log))<0){
				perror("write");
				exit(1);
			}
			printf("Receieved clientId: %s, log: %s",msg.clientId,log);
			close(logFd);
			exit(1);
		}
		else{
			waitpid(pid);
			close(newSockfd);
		}
	}
}
