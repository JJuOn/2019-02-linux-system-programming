#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>

int main(){
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv,&tz);
	printf("%d",tv.tv_sec);
	return 0;
}
