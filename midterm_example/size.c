#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#define MAX_BUF 256
int main(int argc, char** argv){
	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;
	int size;
	if(argc!=2){
		printf("Usage: %s filesize\n",argv[0]);
		exit(0);
	}
	size=atoi(argv[1]);
	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(0);
	}
	while(dep=readdir(dp)){
		if(lstat(dep->d_name,&statbuf)<0){
			perror("lstat");
			continue;
		}
		if(strcmp(dep->d_name,".")==0 || strcmp(dep->d_name,"..")==0){
			continue;
		}
		if(statbuf.st_size>=size){
			printf("%s\n",dep->d_name);
		}
	}
	return 0;
}
