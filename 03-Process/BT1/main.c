#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h>
  
int main(int argc, char const *argv[])
{
    pid_t child_pid;
    int status, retVal;

    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
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