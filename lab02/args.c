#include <stdio.h>

main(int argc, char **argv){
	int i;
	// Prints all arguments
	for (i=0;i<argc;i++){
		printf("argv[%d]=%s\n",i,argv[i]);
	}
}
