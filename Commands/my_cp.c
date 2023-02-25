#include <stdio.h> // printf
#include <unistd.h> // read(), write()
#include <stdlib.h> // exit
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat
#include <utime.h> // utime

#include <string.h>


char* getCopiedFileName(char* copiedFilePath)
{	
	char temp[100] ;
	strncpy(temp, copiedFilePath, 100);
	printf("%s\n", temp);
	
	char* by = "/";
	
	char* ptr = strtok(temp, by);
	char* name;
	while (ptr != NULL) {
		name = ptr;
		printf("'%s'\n", name);
		ptr = strtok(NULL, by);
	}
	
	return name;
}


int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("Invalid command options provided\n ");
        //exit(-1);
    }
	
	char* copiedFilePath = argv[1];
	char* newFilePath = argv[2];		
	char* copiedFileName = getCopiedFileName(copiedFilePath);	
	
	char fullPathOfNewFile[4095];
	snprintf(fullPathOfNewFile, sizeof(fullPathOfNewFile), "%s/%s", newFilePath, copiedFileName);
	
	printf("full path = %s\n", fullPathOfNewFile);
	printf("copiedFilePath = %s\n", copiedFilePath);
	
	int fd = creat(fullPathOfNewFile, 0666);
    if(fd < 0) {
        printf("File not created\n ");
		exit(-1);
    }
	
	int source_fd = open(copiedFilePath, O_RDONLY);
	 if(source_fd < 0){
        printf("File not opened\n ");
		exit(-1);
    }
	
	
	char buf[1];
	int i = 0;
	
    while((i = read(source_fd, buf, 1)) > 0) {        
        write(fd, buf, i);
	}
	
	return 0;
}