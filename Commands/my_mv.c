#include <stdio.h> // printf
#include <unistd.h> // read(), write()
#include <stdlib.h> // exit
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat
#include <utime.h> // utime
#include <string.h> // strncpy()

int isDir(char* argument)
{
	struct stat path;
	stat(argument, &path);

    //return S_ISREG(path.st_mode);
	
	return S_ISDIR(path.st_mode);
}

char* getFileNameFromPath(char* filePath)
{	
	char temp[100] ;
	strncpy(temp, filePath, 100);
	
	char* by = "/";	
	char* name;
	
	char* ptr = strtok(temp, by);
	while (ptr != NULL) {
		name = ptr;
		ptr = strtok(NULL, by);
	}
	
	return name;
}

void createAndCopy(char* newFile, const int source_fd)
{
	int fd = creat(newFile, 0666);
	if(fd < 0) {
		printf("File not created\n ");
		exit(-1);
	}
		
	char buf[1];
	int i = 0;
	while((i = read(source_fd, buf, 1)) > 0) {        
		write(fd, buf, i);
	}
}


int main(int argc, char* argv[])
{
	if(argc != 3){
		printf("Invalid command options provided\n ");
        exit(-1);
	}
	
	char* movedFile = argv[1];
	char* newFile = argv[2];
	
	int source_fd = open(movedFile, O_RDONLY);
		if(source_fd < 0) {
			printf("File not opened\n ");
			exit(-1);
	}	

	if(!isDir(newFile)) {		
		createAndCopy(newFile, source_fd);
	} else {
		char* movedFileName = getFileNameFromPath(movedFile);
		strcat(newFile, "/");
		strcat(newFile, movedFileName);
		
		createAndCopy(newFile, source_fd);
	}
	
	close(source_fd);
	int r = remove(movedFile);
	if (r < 0) {
		printf("%s File is not removed\n", movedFile);
	}
	
	return 0;
}