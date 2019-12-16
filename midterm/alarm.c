#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define MAX_BUF 256

static char word[MAX_BUF];

// Function SigAlrmHandler, it executes banner
void SigAlrmHandler(int signo){
	char* args[3]={"banner",word,NULL};
	if(execvp("banner",args)<0){
		perror("execvp");
		exit(1);
	}
}

int main(int argc,char **argv){
	int pid;
	// Check arguments
	if(argc!=3){
		printf("Usage: %s sec word\n",argv[0]);
		exit(1);
	}
	// Set signalhandler
	signal(SIGALRM,SigAlrmHandler);
	// Copy argv[2] to word
	strcpy(word,argv[2]);
	// Fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(0);
	}
	// In child process
	if(pid==0){
		// alarm to this process about argv[1]
		alarm(atoi(argv[1]));
		for(;;){
			pause();
		}
		exit(0);
	}
	// In parent process
	else
		// wait until child process finishes
		waitpid(pid,NULL,NULL);
	return 0;
}
