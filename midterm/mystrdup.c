#include <stdio.h>
#include <string.h>

#define MAX_BUF 256

// function mystrdup
char *mystrdup(const char* s){
	// Dynamic memory allocation to buf
	char *buf=(char*)malloc(strlen(s)+1);
	// Copy s into buf
	strcpy(buf,s);
	return buf;
}


int main(){
	char str1[]="Hello World!";
	char *str2=mystrdup(str1);
	// Print str2
	puts(str2);
	free(str2);
	return 0;
}
