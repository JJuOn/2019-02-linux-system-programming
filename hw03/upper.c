#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUF 10

int main(int argc, char** argv){
	// File pointer for source text file
	FILE *src;
	// Character pointer buf to store a line of text file
	char *buf;
	// Check arguments
	if(argc!=2){
		printf("Usage: %s source",argv[0]);
		exit(1);
	}
	// Open text file
	if((src=fopen(argv[1],"rt"))==NULL){
		perror("fopen");
		exit(1);
	}
	// Get a line from text file
	while(fgets(buf,MAX_BUF,src)!=NULL){
		// For all characters in string
		while(*buf){
			// If current character is lowercase,
			if(islower(*buf)){
				// Print this character in uppercase
				printf("%c",toupper(*buf));
			}
			// If current character is not lowercase,
			else{
				// Print this character
				printf("%c",*buf);
			}
			// Move to next character
			*buf++;
		}
		// If one line is over, print newline
		printf("\n");
	}
	// Close text file
	fclose(src);
	return 0;
}
