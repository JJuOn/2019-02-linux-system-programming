#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	int fd[2];
	pid_t child;
	// Make a pipe
	if(pipe(fd)==-1){
		perror("pipe");
		exit(1);
	}
	// Fork a process
	child=fork();
	if(child==(pid_t)(-1)){
		perror("fork");
		exit(1);
	}
	// Child process 
	else if(child==(pid_t)0){
		close(1);
		close(fd[0]);
		// Duplicate stdout to fd[1]
		if(dup(fd[1])==-1){
			perror("dup");
			exit(1);
		}
		// Execute ls -l
		if((execlp("ls","ls","-l",NULL))==-1){
			perror("execlp");
			exit(1);
		}
	}
	else{
		close(0);
		close(fd[1]);
		// Duplicate stdin to fd[0]
		if(dup2(fd[0],0)==-1){
			perror("dup");
			exit(1);
		}
		// Execute more
		if((execlp("more","more",NULL))==-1){
			perror("execlp");
			exit(1);
		}
	}
	return 0;
}
