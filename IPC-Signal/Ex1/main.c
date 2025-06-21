#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int sigint_count = 0;

void handle_sigint(int sig) {
    sigint_count++;
    printf("SIGINT received (%d)\n", sigint_count);

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times, exit the program.\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("Program is running.. Press Ctrl+C 3 times to exit the program.\n");
        sleep(1);
    }

    return 0;
}
