#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

main(){
	int n,fd1[2],fd2[2];
	pid_t pid;
	char buf[MAX_BUF];
	// Make two pipes
	if(pipe(fd1)<0 || pipe(fd2)<0){
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
		// Close out of pipe1, in of pipe2
		close(fd1[1]);
		close(fd2[0]);
		printf("Child: Send data to parent\n");
		// Send data to parent via pipe2
		write(fd2[1],buf,n);
		close(fd2[1]);
		sleep(1);
		printf("Child: Wait parent to send data\n");
		// Receive data from parent via pipe1
		if((n=read(fd1[0],buf,MAX_BUF))<0){
			perror("read");
			exit(1);
		}
		printf("Child: Received data from parent\n");
		fflush(stdout);
	}
	// Parent process
	else{
		// Close in of pipe1, out of pipe2
		close(fd1[0]);
		close(fd2[1]);
		strcpy(buf,"Hello, World!\n");
		fflush(stdout);
		printf("Parent: Wait child to send data\n");
		// Receive data from child via pipe2
		if((n=read(fd2[0],buf,MAX_BUF))<0){
			perror("read");
			exit(1);
		}
		printf("Parent: Received data from child\n");
		sleep(1);
		printf("Parent: Send data to child\n");
		// Write data to child via pipe1
		write(fd1[1],buf,n);
		close(fd1[1]);
	}
	exit(0);
}
