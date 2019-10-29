#include <stdio.h>
#include <pthread.h>

// global variable to save result
int sum=0;

// function calculate, it does summation from start to start+50
void calculate(int start){
	int i=0;
	for (i=start;i<start+50;i++){
		sum+=i;
	}
}

main(){
	// declare two tid
	pthread_t tid1,tid2;
	// create a thread whose handler is calculate and its start is 1
	pthread_create(&tid1,NULL,(void *)calculate,(void *)1);
	// create a thread whose handler is calculate and its start is 51
	pthread_create(&tid2,NULL,(void *)calculate,(void *)51);
	// join threads
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	// print result
	printf("result: %d\n",sum);
}
