#include <stdio.h>     // printf() / scanf() / sprintf() ...
#include <stdlib.h>    // exit() / NULL ...
#include <sys/types.h> // time_t / mode_t ...
#include <errno.h>     // errno
#include <string.h>    // strcut() / strcmp() / strerror()

#include <dirent.h>    // opendir() / closedir() / readdir() / dirent / DIR ...


void ls(char* dirName)
{
	DIR* dir;
    struct dirent* dir_entry;

    dir = opendir(dirName);	
    if(dir == NULL) {
        printf("ERROR: %s\n", strerror(errno));
        exit(1);
    }

	while((dir_entry = readdir(dir)) != NULL) {
		
		if(strcmp(dir_entry->d_name, ".") == 0 
        || strcmp(dir_entry->d_name, "..") == 0) {
            continue;
        }
		
		printf("%s  ", dir_entry->d_name);	
	}
	printf("\n");
	
}



int main(int argc, char* argv[]) {
    
	if(argc < 2) {
        ls(".");
        exit(0);
    } 
	
	ls(argv[1]);
	
	
	return 0;
}
