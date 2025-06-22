#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_SIGNALS 5

void sigusr1_handler(int sig) {
    printf("Child: Received signal from parent\n");
}

int main() {pid_t child_pid;
    int status, retVal;

    child_pid = fork();

    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            signal(SIGUSR1, sigusr1_handler);

            /* wait signal from parent process */
            while (1) {
                pause();
            }
        } else {                    /* Parent process */
            for (int i = 0; i < MAX_SIGNALS; ++i) {
                sleep(2);
                printf("Parent: Sending SIGUSR1 to child (count %d)\n", i + 1);
                kill(child_pid, SIGUSR1);
            }

            kill(child_pid, SIGKILL);

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
