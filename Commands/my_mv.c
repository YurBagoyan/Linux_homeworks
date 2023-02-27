#include <stdio.h> // printf
#include <unistd.h> // read(), write()
#include <stdlib.h> // exit
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat
#include <utime.h> // utime
#include <string.h> // strncpy()

int isDir(char* lastArgument)
{
	struct stat path;
	stat(lastArgument, &path);

	printf("+++++++++++");

    return !S_ISREG(path.st_mode);
}

char* getFileNameFromPath(char* movedFilePath)
{	
	char temp[100] ;
	strncpy(temp, movedFilePath, 100);
	
	char* by = "/";	
	char* name;
	
	char* ptr = strtok(temp, by);
	while (ptr != NULL) {
		name = ptr;
		ptr = strtok(NULL, by);
	}
	
	return name;
}

char* getNewFileFullPath(char* newFilePath, char* movedFilePath)
{
	if(!isDir(newFilePath)) {
		return newFilePath;		
	}
	
	char* movedFileName = getFileNameFromPath(movedFilePath);
	char* newFileFullPath;	
	
	snprintf(newFileFullPath, sizeof(newFileFullPath), "%s/%s", newFilePath, movedFileName);
	return newFileFullPath;
}

int main(int argc, char* argv[])
{
	
	printf("----------%s", argv[2]);
	if(argc != 3){
		printf("Invalid command options provided\n ");
        exit(-1);
	}
	
	char* movedFilePath = argv[1];
	char* newFilePath = argv[2];	
	
	printf("moved %s", movedFilePath);
	printf("new %s", newFilePath);
		
	char* newFileFullPath = getNewFileFullPath(newFilePath, movedFilePath);
	
	int fd = creat(newFileFullPath, 0666);
    if(fd < 0) {
        printf("File not created\n ");
		exit(-1);
    }

	int source_fd = open(movedFilePath, O_RDONLY);
	if(source_fd < 0) {
        printf("File not opened\n ");
		exit(-1);
    }	
	
	char buf[1];
	int i = 0;
    while((i = read(source_fd, buf, 1)) > 0) {        
        write(fd, buf, i);
	}
	
	close(source_fd);
	return 0;
	
}