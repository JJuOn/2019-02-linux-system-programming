#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main(){
	pid_t pid;
	char *argv[]={"mycp","exec.c","exec2.c",NULL};
	if((pid=fork()<0)){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		if(execl("/home/lsp23/lab04/mycp",argv[0],argv[1],argv[2],argv[3])<0){
			perror("execl");
			exit(1);
		}
	}
	if(waitpid(pid,NULL,0)<0){
		perror("waitpid");
		exit(1);
	}

	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		if(execv("/home/lsp23/lab04/mycp",argv)<0){
			perror("execv");
			exit(1);
		}
	}
	if(waitpid(pid,NULL,0)<0){
		perror("waitpid");
		exit(1);
	}
	
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		if(execlp("env","env",NULL)<0){
			perror("execlp");
			exit(1);
		}
	}
	if(waitpid(pid,NULL,0)<0){
		perror("waitpid");
		exit(1);
	}
}
