#include <stdio.h>
#include <signal.h>

void SigAlarmHandler(int signo){
	return;
}

unsigned int mysleep(unsigned int nsecs){
	if(signal(SIGALRM,SigAlarmHandler)==SIG_ERR){
		return nsecs;
	}
	alarm(nsecs);
	pause();
	return alarm(0);
}

main(){
	printf("Wait for 5 seconds...\n");
	mysleep(5);
}
