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
    int status;
    int exit_code = 5;

    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            printf("My PID is: %d, my parent PID is: %d, I will end with exit code %d\n", getpid(), getppid(), exit_code);
            sleep(9); /* while waiting, try to kill this process unusually */
            exit(exit_code);
        } else {                    /* Parent process */
            printf("My PID is: %d, waiting for my child %d to end ...\n", getpid(), child_pid);
            wait(&status);
            if (WIFEXITED(status)) {
                printf("Parent: my child %d ended normally with exit code = %d.\n",child_pid, WEXITSTATUS(status));
            } else {
                printf("Parent: my child %d ended unusually.\n", child_pid);
            }
        }
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    return 0;
} 