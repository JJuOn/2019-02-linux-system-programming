#include <stdio.h>
#include <unistd.h>

//modified
main(int argc,char *argv[]){
	if(argc!=3){
		fprintf(stderr,"Usage: %s source destination\n",argv[0]);
		exit(1);
	}
	if(link(argv[1],argv[2])<0){
		perror("link");
		exit(1);
	}
}
