#include <stdio.h>
#include <fcntl.h>  // creat 
#include <sys/stat.h> // stat


void touch(char* filePath)
{
    struct stat st;

    if (stat(filePath, &st) == 0) {
    /* File exists, update access and modification times */
        printf("Already have file: ", filePath);
        utimes(filePath, NULL);
    } else {
        int fd = creat(filePath, 0666);
        if(fd < 0) {
            printf("Can't create file: %s/n", filePath);
        } 
    }   
}

int isDir(char* lastArgument)
{
    struct stat path;
    stat(lastArgument, &path);

    return S_ISREG(path.st_mode);
}

int main(int argc, char* argv[])
{
    if(argc < 2) {
        printf("Invalid options provided\n");
        return -1;
    }

    char* path = argv[argc-1];
    if(!isDir(path)) {
        printf("Last one is dir\n");
    } else {
        printf("Last argument is not dir. Path = ./\n");
        path = "./";
    }

    for(int i = 1; i < argc; ++i) {
        char fullPath[4095];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, argv[i]);


        printf(fullPath); printf("\n");
        //touch(fullPath);
    }  

    return 0;
}
