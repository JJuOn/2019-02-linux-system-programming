#include <stdio.h>

#define MAX_BUF 1024

main(int argc,char* argv[]){
	FILE *src,*dst;
	char buf[MAX_BUF];
	int count;
	if(argc!=3){
		fprintf(stderr,"Usage: %s source destination\n",argv[0]);
		exit(1);
	}
	if((src=fopen(argv[1],"rb"))==NULL){
		perror("fopen");
		exit(1);
	}
	if((dst=fopen(argv[2],"wb"))==NULL){
		perror("fopen");
		exit(1);
	}
	while(count=fread(buf,sizeof(char),1,src)){
		fwrite(buf,1,count,dst);
	}
	fclose(src);
	fclose(dst);
}
