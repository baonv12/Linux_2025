#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <poll.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void sigint_handler(int sig) {
    sigint_flag = 1;
}

void sigterm_handler(int sig) {
    sigterm_flag = 1;
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    char buffer[1024];
    struct pollfd fds[1];

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    printf("Program started. Type something or press Ctrl+C / send SIGTERM.\n");

    while (1) {
        int ret = poll(fds, 1, -1);

        if (ret == -1) {
            perror("poll failed");
            break;
        }

        /* check data from stdin */
        if (fds[0].revents & POLLIN) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("You typed: %s", buffer);
            }
        }

        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }

        if (sigterm_flag) {
            printf("SIGTERM received. Exiting...\n");
            break;
        }
    }

    return 0;
}
