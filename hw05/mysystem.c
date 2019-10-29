#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 256
// function which executes command
int mysystem(char *cmd){
	// char* arguments, command will be exected via /bin/bash -c
	char *argv[]={"/bin/bash", "-c", cmd, "\0"};
	int pid;
	// fork a process
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	// if it is child process, execute the command	
	if(pid==0){
		execv("/bin/bash",argv);
		exit(1);
	}
	// wait until child process's termination
	waitpid(pid,NULL,NULL);
	return 0;
}

int main(int argc, char *argv[]){
	char cmd[MAX_CMD];
	while(1){
		printf("$ ");
		// get command from user
		fgets(cmd,MAX_CMD,stdin);
		// if command starts with 'q', escape the loop
		if(cmd[0]=='q'){
			break;
		}
		// do command
		mysystem(cmd);
	}
	return 0;
}
