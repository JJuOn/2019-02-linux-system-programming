#include <stdio.h>
#include <pthread.h>
#include <string.h>
#define MAX_BUF 256

// Function countLower, it returns count of lower character of a file
int countLower(char* filename){
	FILE* fd;
	int i,count=0;
	char buf[MAX_BUF];
	// If fopen failed, exit program
	if((fd=fopen(filename,"rt"))==NULL){
		perror("fopen");
		exit(1);
	}
	// Read a file line by line
	while(fgets(buf,MAX_BUF,fd)!=NULL){
		// if one character is lowercase, increase count
		for(i=0;i<strlen(buf);i++){
			if(islower(buf[i]))
				count++;
		}
	}
	return count;
}

int main(int argc, char**argv){
	pthread_t *tid;
	int *result;
	// Check arguments
	if(argc==1){
		printf("Usage: %s file1 file2 ...\n",argv[0]);
		exit(0);
	}
	int size=argc-1,i;
	// Dynamic memory allocation of tid, result
	tid=(pthread_t*)malloc(size*sizeof(pthread_t));
	result=(int*)malloc(size*sizeof(int));
	// Create threads
	for(int i=0;i<size;i++){
		pthread_create(&tid[i],NULL,(void*)countLower,argv[i+1]);
	}
	// Join Threads
	for(int i=0;i<size;i++){
		pthread_join(tid[i],&result[i]);
	}
	// Print filename and results
	for(int i=0;i<size;i++){
		printf("%s: %d\n",argv[i+1],result[i]);
	}
	// Free memories
	free(tid);
	free(result);
	return 0;
}
