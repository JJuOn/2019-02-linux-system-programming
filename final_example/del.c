#include <stdio.h>
#include <string.h>

void del(char str[]){
	int i;
	char* temp=(char*)malloc(20*sizeof(char));
	for(i=1;str[i]!='\0';i++){
		temp[i-1]=str[i];
	}
	temp[i-1]='\0';
	strcpy(str,temp);
}

main(){
	char str[20]="Hello";
	del(str);
	puts(str);
}
