#include <stdio.h>
#include <string.h>

void strupper(char str[]){
	int size=strlen(str),i;
	for(i=0;i<size;i++){
		str[i]=toupper(str[i]);
	}
}

int main(){
	char str[]="Hello, world!";
	strupper(str);
	printf("%s\n",str);
	return 0;
}
