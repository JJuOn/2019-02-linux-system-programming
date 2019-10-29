#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char *argv[]){
	if(argc!=2){
		fprintf(stderr,"Usage: %s dirname\n",argv[0]);
		exit(1);
	}
	if(mkdir(argv[1],755)<0){
		perror("mkdir");
		exit(1);
	}
}
