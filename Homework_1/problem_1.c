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

char* get_file_name(char* path) {
    // Find the last occurrence of '/' or '\' in the path
    char* last_slash = strrchr(path, '/');
    if (!last_slash) {
        last_slash = strrchr(path, '\\');
    }
    if (!last_slash) {
        // No slash found, so return the original path
        return path;
    } else {
        // Return the substring after the last slash
        return last_slash + 1;
    }
}

void createAndCopy(char* newFile, const int source_fd)
{
	// Create new file
	int dest_fd = creat(newFile, 0666);
	if(dest_fd < 0) {
		printf("File not created\n ");
		exit(-1);
	}
	
	// Copy data
	char buf[1];
	int i = 0;
	while((i = read(source_fd, buf, 1)) > 0) {        
		write(dest_fd, buf, i);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != 3) {
		printf("Invalid command options provided\n ");
        exit(-1);
	}
	
	char* sourceFilePath = argv[1];
	char* newFilePath = argv[2];	
	
	// Open souorce file
	int source_fd = open(sourceFilePath, O_RDONLY);
	if(source_fd < 0) {
		printf("File not opened\n ");
		exit(-1);
	}
	
	if(isDir(newFilePath)) {		
		char* sourceFileName = get_file_name(sourceFilePath);
		strcat(newFilePath, "/");
		strcat(newFilePath, sourceFileName);
	}
	
	createAndCopy(newFilePath, source_fd);
	
	close(source_fd);
	return 0;
}