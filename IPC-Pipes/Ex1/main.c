#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MSG_SIZE    20

char message[] = "Hello this is parent!";
char buffer[MSG_SIZE];
int fds[2], i;

int main(int argc, char const *argv[])
{
    pid_t child_pid;

    if (pipe(fds) < 0) {
        printf("pipe() unsuccessfully\n");
        exit(1);
    }

    child_pid = fork();
    
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Children process */
            close(fds[1]);
            read(fds[0], buffer, MSG_SIZE);
            printf("Hi, I'm reader\n");
            printf("Got this message from parent: %s\n", buffer);
            close(fds[0]);
        } else {                    /* Parent process */
            close(fds[0]);
            printf("Hi, I'm writer\n");
            write(fds[1], message, strlen(message));
            close(fds[1]);
        }
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    return 0;
}