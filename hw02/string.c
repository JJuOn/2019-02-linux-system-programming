#include <stdio.h>

int strlen_p(char* str){
	int len=0;
	while(*str++){
		len++;
	}
	return len;
}

int strlen_a(char str[]){
	int i;
	for(i=0;str[i]!='\0';i++);
	return i;
}

void strcpy_p(char* dst, char* src){
	while(*src){
		*dst++=*src++;
	}
	*dst=*src;
}

void strcpy_a(char dst[],char src[]){
	int i;
	for(i=0;src[i]!='\0';i++){
		dst[i]=src[i];
	}
	dst[i]=src[i];
}

void strcat_p(char *dst,char *src){
	while(*dst++);
	*dst--;
	while(*src){
		*dst++=*src++;
	}
	*dst=*src;
}

void strcat_a(char dst[],char src[]){
	int i,j;
	for(i=0;dst[i]!='\0';i++);
	for(j=0;src[j]!='\0';j++){
		dst[i+j]=src[j];
	}
	dst[i+j]='\0';
}
/*
[Function Name]: int strcmp_p(char* dst, char* src)
[Description]:
	- Implement strcmp function using pointer.
	- If dst is longer than src, this function returns 1.
	- If dst equals src, this function returns 0.
	- If dst is shorter then src, this function returns -1.
[Input]:
	char* dst // destination
	char* src // source
[Output]:
	int strcmp_p()
[Call By]:
	main()
[Calls]:
	Nothing.
[Returns]:
	Nothing.
*/
int strcmp_p(char* dst, char* src){
	while(*dst || *src){
		if(*dst==*src){
			*dst++;
			*src++;
		}
		else if((int)*dst<(int)*src){
			return -1;
		}
		else{
			return 1;
		}
	}
	return 0;
}
/*
[Function Name]: int strcmp_a(char dst[], char src[])
[Description]:
	- Implement strcmp function using character array.
	- If dst is longer then src, this function returns 1.
	- If dst equals src, this function returns 0.
	- If dst is shorter than src, this function return -1.
[Input]:
	char dst[] // destination
	char src[] // source
[Output]:
	int strcmp_a();
[Call By]:
	main()
[Calls]:
	Nothing.
[Returns]:
	Nothing.
*/
int strcmp_a(char dst[],char src[]){
	int i=0,j=0;
	while(dst[i]!='\0' || src[i]!='\0'){
		if(dst[i]==src[i]){
			i++;
			j++;
		}
		else if((int)dst[i]<(int)src[i]){
			return -1;
		}
		else{
			return 1;
		}
	}
	return 0;
}
/*
[Program Name]: HW02/string
[Description]: 
	- Implement string related function and Test these functions.
[Input]:
	Nothing.
[Output]:
	Nothing.
[Calls]:
	int strlen_p();
	int strlen_a();
	void strcpy_p();
	void strcpy_a();
	void strcat_p();
	void strcat_a();
	int strcmp_p();
	int strcmp_a();
[특기사항]:
	Nothing.
*/
main(){
	int len1,len2;
	char str1[20],str2[20];

	len1=strlen_p("Hello");
	len2=strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n",len1,len2);

	strcpy_p(str1,"Hello");
	strcpy_a(str2,"Hello");
	printf("strcpy: p=%s, a=%s\n",str1,str2);

	strcat_p(str1,", World!");
	strcat_a(str2,", World!");
	printf("strcat: p=%s, a=%s\n",str1,str2);
	printf("strcmp:\n");
	printf("aaa, bbb, p=%d, a=%d\n",strcmp_p("aaa","bbb"),strcmp_a("aaa","bbb"));
	printf("aaa, aaaa, p=%d, a=%d\n", strcmp_p("aaa","aaaa"),strcmp_a("aaa","aaaa"));
	printf("aaaa, aaa, p=%d, a=%d\n", strcmp_p("aaaa","aaa"),strcmp_a("aaaa","aaa"));
}
