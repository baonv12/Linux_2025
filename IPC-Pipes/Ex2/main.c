#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MSG_SIZE    100

char message[] = "Hello from parent";
char buffer[MSG_SIZE];
int fds1[2];
int fds2[2];

int main(int argc, char const *argv[])
{
    pid_t child1_pid;
    pid_t child2_pid;

    if ((pipe(fds1) < 0) || (pipe(fds2) < 0)) {
        printf("pipe() unsuccessfully\n");
        exit(1);
    }

    child1_pid = fork();   
    if (child1_pid >= 0) {
        if (0 == child1_pid) {       /* Children process */
            close(fds1[1]);
            close(fds2[0]);

            /* read message from parent */
            read(fds1[0], buffer, MSG_SIZE);
            printf("Hi, I'm child 1\n");
            printf("Child1: Got this message from parent: %s\n", buffer);

            /* modify message received from parent then send to child 2 */
            strcat(buffer, " and child 1!");
            write(fds2[1], buffer, strlen(buffer));

            close(fds1[0]);
            close(fds2[1]);
            exit(0);
        } 
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    child2_pid = fork();
    if (child2_pid >= 0) {
        if (0 == child2_pid) {       /* Children process */
            close(fds1[1]); close(fds1[0]);
            close(fds2[1]);

            /* read message from child 2 */
            read(fds2[0], buffer, MSG_SIZE);
            printf("Hi, I'm child 2\n");
            printf("Child2: Got this message from child 1: %s\n", buffer);

            close(fds2[0]);
            exit(0);
        } 
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    /* Parent */
    close(fds1[0]);
    close(fds2[0]); close(fds2[1]);

    /* Send to child 1 */
    write(fds1[1], message, strlen(message));
    close(fds1[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}