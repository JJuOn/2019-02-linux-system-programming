#include <stdio.h>

int main(int argc, char **argv){
	int i;
	if(argc==1){
		printf("Usage: %s file1 file2 ...\n",argv[0]);
		exit(0);
	}
	for(i=1;i<argc;i++){
		if(remove(argv[i])<0){
			perror("remove");
			exit(0);
		}
	}
	return 0;
}
