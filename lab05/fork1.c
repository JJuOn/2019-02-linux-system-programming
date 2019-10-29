#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main(){
	int pid;
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		printf("I am %d. My parent is %d.\n",getpid(),getppid());
	}
	else{
		printf("I am %d. My child is %d.\n",getpid(),pid);
	}

}
