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

    return !S_ISREG(path.st_mode);
}

char* getMovedFileName(char* movedFilePath)
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

int main(int argc, char* argv[])
{
	if(argc != 3){
		printf("Invalid command options provided\n ");
        //exit(-1);
	
	char* movedFilepath = argv[1];
	char* newFilePath = argv[2];
	
	if(isDir(newFilePath) 
	{
		
	}


	return 0;
	
}