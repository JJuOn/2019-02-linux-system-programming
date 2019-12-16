#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char** argv){
	int fdin,fdout;
	char *src,*dst;
	struct stat statbuf;
	// Check arguments
	if(argc!=3){
		fprintf(stderr,"Usage: %s source destination\n",argv[0]);
		exit(1);
	}
	// Open source file
	if((fdin=open(argv[1],O_RDONLY))<0){
		perror("open");
		exit(1);
	}
	// Open destination file
	if((fdout=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0644))<0){
		perror("open");
		exit(1);
	}
	// Get source file's stat
	if(fstat(fdin,&statbuf)<0){
		perror("fstat");
		exit(1);
	}
	// Move file pointer
	if(lseek(fdout,statbuf.st_size-1,SEEK_SET)<0){
		perror("lseek");
		exit(1);
	}
	// Write fdout to 1
	write(fdout,"",1);
	// Memmory map
	if((src=mmap(0,statbuf.st_size,PROT_READ,MAP_SHARED,fdin,0))==(caddr_t)-1){
		perror("mmap");
		exit(1);
	}
	// Memory map
	if((dst=mmap(0,statbuf.st_size,PROT_WRITE,MAP_SHARED,fdout,0))==(caddr_t)-1){
		perror("mmap");
		exit(1);
	}
	// Copy source memory to destination memory
	memcpy(dst,src,statbuf.st_size);
	// Close files
	close(fdin);
	close(fdout);
	return 0;
}
