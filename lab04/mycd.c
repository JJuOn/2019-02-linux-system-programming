#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[]){
	if(argc!=2){
		fprintf(stderr,"Usage: %s dirname\n",argv[0]);
		exit(0);
	}
	if(chdir(argv[1])<0){
		perror("chdir");
		exit(1);
	}
}
