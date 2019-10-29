#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(){
	umask(0);
	if(creat("bar",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)<0){
		perror("creat");
		exit(1);
	}
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWGRP | S_IWOTH);
	if(creat("foo",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)<0){
			perror("creat");
			exit(1);
	}
}
