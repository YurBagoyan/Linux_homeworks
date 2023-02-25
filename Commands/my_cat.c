#include <stdio.h> // printf
#include <unistd.h> // read(), write()
#include <stdlib.h> // exit
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat
#include <utime.h> // utime
#include <string.h> // strncpy()

int main(int argc, char* argv[])
{
	char* filePath = argv[1];
	
	int source_fd  = open(filePath, O_RDONLY);
	if(source_fd < 0){
        printf("File not opened\n");
		exit(-1);
    }
	
	char buf[1];
	int i = 0;
	while((i = read(source_fd, buf, 1)) > 0) {        
		printf("%s", buf);
	}
	
	close(source_fd);
}