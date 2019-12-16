#include <stdio.h>
#include <string.h>

#define MAX_BUF 256
int main(int argc,char** argv){
	int num,i;
	char buf[MAX_BUF],c[MAX_BUF];
	// Check argument counts,
	if(argc!=2){
		printf("Usage: %s number",argv[0]);
		exit(0);
	}
	// Convert argv[1] to integer
	num=atoi(argv[1]);
	// Initialize buf and c
	strcpy(buf,"");
	strcpy(c,"");
	// while num is not zero
	while(num){
		// Copy remainder to c
		sprintf(c,"%d",num%2);
		// Put c into end of buf
		strcat(buf,c);
		// Divide num into 2
		num/=2;
	}
	// Print buf reversely
	for(int i=strlen(buf);i>=0;i--){
		printf("%c",buf[i]);
	}
	printf("\n");
	return 0;
}
