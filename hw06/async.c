#include <stdio.h>
#include <signal.h>

// SIGCHLD handler, this handler simply print a line
void SigChldHandler(int signo){
	printf("Child processs has been terminated.\n");
}

int main(){
	pid_t pid;
	// Set signal handler
	signal(SIGCHLD,SigChldHandler);
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// If this process is a child process
	if(pid==0){
		// kill this process after 5 seconds
		printf("Child process will be terminated after 5 seconds.\n");
		sleep(5);
		exit(0);
	}
	// If this process is a parent process 
	else{
		// do parent process's job independently
		printf("Parent process is doing something\n");
		while(1);
	}
	return 0;
}
