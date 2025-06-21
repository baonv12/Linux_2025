#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MSG_SIZE    100

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
            ssize_t num_bytes = read(fds[0], buffer, MSG_SIZE);
            printf("Hi, I'm reader\n");
            if (num_bytes > 0) {
                buffer[num_bytes] = '\0'; /* add end of string */
                int count = strlen(buffer);
                printf("Got this message from parent: %s\n", buffer);
                printf("Number of characters of the message = %d\n", count);
            } else {
                printf("No data received.\n");
            }

            close(fds[0]);
            exit(0);
        } else {                    /* Parent process */
            close(fds[0]);

            printf("Hi, I'm writer\n");
            write(fds[1], message, strlen(message));
            close(fds[1]);

            wait(NULL);
        }
    } else {
        printf("fork() unsuccessfully\n");      /* fork() returns -1 if failed */
        return 1;
    }

    return 0;
}