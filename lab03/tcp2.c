#include <stdio.h>

#define MAX_BUF 256

main(int argc, char* argv[]){
	FILE *src,*dst;
	char buf[MAX_BUF];
	if(argc!=3){
		fprintf(stderr,"Usage: %s source destination\n",argv[0]);
		exit(1);
	}
	if((src=fopen(argv[1],"rt"))==NULL){
		perror("fopen");
		exit(1);
	}
	if((dst=fopen(argv[2],"wt"))==NULL){
		perror("fopen");
		exit(1);
	}
	while(fgets(buf,MAX_BUF,src)){
		fputs(buf,dst);
	}
	fclose(src);
	fclose(dst);
}
