#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
  
int main (void) 
{ 
    int fd; 
    int numb_write;
  
    // assume hello.txt is already created 
    fd = open("hello.txt", O_WRONLY | O_APPEND);         
    if (-1 == fd) { 
	printf("open() hello.txt failed\n");
    }      
  
    lseek(fd, 0, SEEK_SET);
    numb_write = write(fd, "hello", strlen("hello"));
    printf("Write %d bytes to hello.txt\n", numb_write);
    
    close(fd); 
  
    return 0; 
} 