#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0;

void handle_alarm(int sig) {
    seconds++;
    printf("Timer: %d seconds\n", seconds);

    if (seconds >= 10) {
        printf("10 seconds have elapsed. Exit program.\n");
        exit(0);
    }

    alarm(1);
}

int main() {
    signal(SIGALRM, handle_alarm);

    alarm(1);

    while (1) {
        pause(); /* wait for signals without busy-waiting */
    }

    return 0;
}
