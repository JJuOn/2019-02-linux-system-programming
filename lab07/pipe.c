#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

main(){
	int n,fd[2];
	pid_t pid;
	char buf[MAX_BUF];
	// Make a pipe
	if(pipe(fd)<0){
		perror("pipe");
		exit(1);
	}
	// Fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// Child process
	else if(pid==0){
		close(fd[1]);
		printf("Child: Wait parent to send data\n");
		// Read buf from pipe, if unavailable, wait
		if((n=read(fd[0],buf,MAX_BUF))<0){
			perror("read");
			exit(1);
		}
		printf("Child: Received data from parent:");
		// Flush stdout
		fflush(stdout);
		// Write buf
		write(STDOUT_FILENO,buf,n);
	}
	// Parent process
	else{
		close(fd[0]);
		strcpy(buf,"Hello, World!\n");
		printf("Parent: Send data to child\n");
		// Write buf to child
		write(STDIN_FILENO,buf,n);
	}
	exit(0);
}
