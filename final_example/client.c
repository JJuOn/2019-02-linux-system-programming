#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp.h"

typedef struct{
	int type;
	char clientId[100];
} MsgType;

int main(int argc,char **argv){
	int sockfd, n;
	struct sockaddr_in servAddr;
	MsgType msg;
	struct hostent *hp;
	if(argc!=3){
		fprintf(stderr,"Usage: %s address clientid\n",argv[0]);
		exit(1);
	}
	if((sockfd=socket(PF_INET,SOCK_STREAM,0))<0){
		perror("socket");
		exit(1);
	}
	bzero((char*)&servAddr,sizeof(servAddr));
	servAddr.sin_family=PF_INET;
	servAddr.sin_port=htons(SERV_TCP_PORT);
	if(isdigit(argv[1][0])){
		servAddr.sin_addr.s_addr=inet_addr(argv[1]);
	}
	else{
		if((hp=gethostbyname(argv[1]))==NULL){
			fprintf(stderr,"Unknown host: %s\n",argv[1]);
		}
		memcpy(&servAddr.sin_addr,hp->h_addr,hp->h_length);
	}
	if(connect(sockfd,(struct sockaddr *)&servAddr,sizeof(servAddr))<0){
		perror("connect");
		exit(1);
	}
	msg.type=MSG_REQUEST;
	strcpy(msg.clientId,argv[2]);
	if(write(sockfd,&msg,sizeof(msg))<0){
		perror("write");
		exit(1);
	}
	close(sockfd);
}
