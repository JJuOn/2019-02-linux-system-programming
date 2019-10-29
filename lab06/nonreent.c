#include <stdio.h>
#include <signal.h>
#include <pwd.h>

void MyAlarmHandler(int signo){
	struct passwd *rootptr;
	signal(SIGALRM,MyAlarmHandler);
	alarm(1);
	printf("in signal handler\n");
	if((rootptr=getpwnam("root"))==NULL){
		perror("getpwnam");
		exit(1);
	}
	return;
}

main(){
	struct passwd *ptr;
	signal(SIGALRM,MyAlarmHandler);
	alarm(1);
	for(;;){
		if((ptr=getpwnam("lsp23"))==NULL){
			perror("getpwnam");
			exit(1);
		}
		if(strcmp(ptr->pw_name,"lsp23")!=0){
			printf("return value corrupted!, pw_name=%s\n",ptr->pw_name);
			exit(1);
		}
	}
}
