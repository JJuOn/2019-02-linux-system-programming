#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>

#define MAX_BUF 1024

void getUname(uid_t uid, char* buf){
	struct passwd *pwd;
	pwd=getpwuid(uid);
	strcpy(buf,pwd->pw_name);
	return;
}
void getGname(gid_t gid, char* buf){
	struct group *g;
	g=getgrgid(gid);
	strcpy(buf, g->gr_name);
	return;
}

void getMode(mode_t st_mode, char* buf){
	char result[MAX_BUF];
	if(S_ISDIR(st_mode))
		strcpy(result,"d");
	else
		strcpy(result,"-");
	if(st_mode & S_IRUSR)
		strcat(result,"r");
	else
		strcat(result,"-");
	if(st_mode & S_IWUSR)
		strcat(result,"w");
	else
		strcat(result,"-");
	if(st_mode & S_IXUSR)
		strcat(result,"x");
	else
		strcat(result,"-");
	if(st_mode & S_IRGRP)
		strcat(result,"r");
	else
		strcat(result,"-");
	if(st_mode & S_IWGRP)
		strcat(result,"w");
	else
		strcat(result,"-");
	if(st_mode & S_IXGRP)
		strcat(result,"x");
	else
		strcat(result,"-");
	if(st_mode & S_IROTH)
		strcat(result,"r");
	else
		strcat(result,"-");
	if(st_mode & S_IWOTH)
		strcat(result,"w");
	else
		strcat(result,"-");
	if(st_mode & S_IXOTH)
		strcat(result,"x");
	else
		strcat(result,"-");
	strcpy(buf, result);
	return;
}

int main(){
	DIR *dp;
	struct dirent *dep;
	char d_name[MAX_BUF],lastModified[MAX_BUF],uname[MAX_BUF],gname[MAX_BUF],mode[MAX_BUF];
	struct stat statbuf;
	struct tm *mtime;
	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(0);
	}
	while(dep=readdir(dp)){
		strcpy(d_name,dep->d_name);
		if(strcmp(d_name,".")==0 || strcmp(d_name,"..")==0)
			continue;
		if(lstat(d_name,&statbuf)<0){
			perror("lstat");
			continue;
		}
		if((mtime=localtime(&(statbuf.st_mtime)))==NULL){
			perror("localtime");
			continue;
		}
		if(strftime(lastModified, MAX_BUF, "%b %d %H:%M", mtime)==0){
			perror("strftime");
			continue;
		}
		getMode(statbuf.st_mode,mode);
		getUname(statbuf.st_uid,uname);
		getGname(statbuf.st_gid,gname);
		printf("%s\t%d\t%s\t%s\t%d\t%s\t%s\n", mode, statbuf.st_nlink, uname, gname, statbuf.st_size, lastModified, d_name);
	}
	return 0;
}
