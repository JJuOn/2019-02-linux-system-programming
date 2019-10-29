#include <stdio.h>
#include <string.h>

#define MAX_BUF 256

int main(int argc, char**argv){
	FILE *fd;
	int count=0;
	char buf[MAX_BUF];
	if(argc!=2){
		printf("Usage: %s source\n",argv[0]);
		exit(1);
	}
	if((fd=fopen(argv[1],"rt"))==NULL){
		perror("fopen");
		exit(1);
	}
	while(fgets(buf,MAX_BUF,fd)!=NULL){
		char* tok;
		tok=strtok(buf," ");
		while(tok!=NULL){
			count++;
			tok=strtok(NULL," ");
		}
	}
	printf("%d\n",count);
	fclose(fd);
	return 0;
}
