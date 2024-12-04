#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  // Include this header for pid_t
#include <sys/wait.h>   // Include this header for wait() system call


int main() {
    pid_t p1, p2;

    // Create first child P1
    p1 = fork();
    if (p1 < 0) {
        perror("Fork failed for P1");
        exit(1);
    }

    if (p1 == 0) {
        // Inside P1
        p2 = fork();
        if (p2 < 0) {
            perror("Fork failed for P2");
            exit(1);
        }

        if (p2 == 0) {
            // Inside P2: Replace content with active processes
            execlp("ps", "ps", "-e", NULL);
            perror("execlp failed for P2");
            exit(1);
        } else {
            // P1 waits for P2
            wait(NULL);
        }
    } else {
        // Parent waits for P1
        wait(NULL);
    }

    return 0;
}
