#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h>

void sigusr1_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Child: got signal SIGUSR1 from Parent!\n");
    }
}

int main(int argc, char const *argv[])
{
    pid_t child_pid;
    int status, retVal;

    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            printf("Child process termiation.\n");
            
        } else {                    /* Parent process */
            printf("My PID is: %d, my child PID is: %d\n", getpid(), child_pid);
            while(1);
            retVal = wait(&status);
            if(retVal == -1){
                printf("wait() unsuccessfully\n"); 
                return 1;
            }
        }
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    return 0;
} 
