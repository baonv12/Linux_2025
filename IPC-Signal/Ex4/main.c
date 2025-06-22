#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigtstp_handler(int sig) {
    printf("\nSIGTSTP ignored\n");
    fflush(stdout);
}

int main() {
    signal(SIGTSTP, sigtstp_handler);

    while (1) {
        printf("Running... Press Ctrl+Z to send SIGTSTP.\n");
        sleep(1);
    }

    return 0;
}
