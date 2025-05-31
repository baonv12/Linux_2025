#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h> 

int main(int argc, char *argv[]) {

    const char *filename = argv[1];
    int fd;

    fd = open(filename, O_RDONLY);         
    if (-1 == fd) { 
        printf("open file failed\n");
        return 1;
    } 

    struct stat file_stat;
    if (lstat(filename, &file_stat) == -1) {
        printf("get file stat failed\n");
        return 1;
    }

    printf("File name: %s\n", filename);

    switch (file_stat.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n"); break;
        case S_IFCHR:  printf("character device\n"); break;
        case S_IFDIR:  printf("directory\n"); break;
        case S_IFIFO:  printf("FIFO/pipe\n"); break;
        case S_IFLNK:  printf("symlink\n"); break;
        case S_IFREG:  printf("regular file\n"); break;
        case S_IFSOCK: printf("socket\n"); break;
        default:       printf("unknown?\n"); break;
    }

    printf("Last file modification: %s", ctime(&file_stat.st_mtime));
    printf("File size: %ld bytes\n", file_stat.st_size);

    return 0;
}