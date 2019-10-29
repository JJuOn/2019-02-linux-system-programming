#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

main(){
	DIR *dp;
	struct dirent *dep;
	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(0);
	}
	while((dep=readdir(dp))!=NULL){
		printf("%s\n",dep->d_name);
	}
	closedir(dp);
}
