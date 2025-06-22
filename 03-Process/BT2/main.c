#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h>
  
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Please pass an argument\n");
        return 1;
    }
    const char *cmd = argv[1];
    pid_t child_pid;
    int status, retVal;

    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            if (strcmp(cmd, "1") == 0) {
                execlp("ls", "ls", "-l", NULL);
            } else if (strcmp(cmd, "2") == 0){
                execlp("date", "date", NULL);
            } else {
                printf("Unknown command\n");
                exit(1);
            }
            printf("execlp() failed\n");
            exit(1);
        } else {                    /* Parent process */
            retVal = wait(&status);
            if(retVal == -1){
                printf("wait() unsuccessfully\n"); 
                return 1;
            }
            printf("My PID is: %d, my child PID is: %d\n", getpid(), child_pid);
        }
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    return 0;
} 