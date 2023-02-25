#include <stdio.h> // printf
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat
#include <utime.h> // utime

int isDir(char* lastArgument)
{
	struct stat path;
    	stat(lastArgument, &path);

    	return S_ISREG(path.st_mode);
}

char* getPath(char* path, int* fileNameCount)
{
	if(!isDir(path)) {
        printf("Last one is directory. Files created in %s%s", path, " directory\n");
		*fileNameCount = *fileNameCount - 1;
		return path;		
    
	} else {
		printf("Last argument is not directory. Files created in current directory\n");
        return "./";
    }
}

void touch(char* filePath)
{
    struct stat st;

	if (stat(filePath, &st) == 0) {
	/* File exists, update access and modification times */
		utime(filePath, NULL);
    
	} else {
		int fd = creat(filePath, 0666);
        
		if(fd < 0) {
        printf("Can't create file: %s%s", filePath,  "\n");
        } 
    }   
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
       	printf("Invalid options provided\n");
       	return -1;
   	}

	int fileNameCount = argc;
   	char* path = getPath(argv[argc-1], &fileNameCount);  

    for(int i = 1; i < fileNameCount; ++i) {
	char fullPath[4095];		
       	snprintf(fullPath, sizeof(fullPath), "%s/%s", path, argv[i]);
       	touch(fullPath);
    }  

   	return 0;
}
