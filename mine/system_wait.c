#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t p1, p2;

    // Step 1: Print the parent process ID (P)
    printf("Parent PID: %d\n", getpid());

    // Step 2: Create the first child process (P1)
    p1 = fork();
    if (p1 < 0) {  // If fork fails
        perror("Fork failed for P1");
        exit(1);
    }

    if (p1 == 0) {  // Inside P1 (Child Process)
        printf("P1 PID: %d, Parent PID: %d\n", getpid(), getppid());

        // Step 3: Create the second child process (P2)
        p2 = fork();
        if (p2 < 0) {  // If fork fails
            perror("Fork failed for P2");
            exit(1);
        }

        if (p2 == 0) {  // Inside P2 (Child of P1)
            printf("P2 PID: %d, Parent PID: %d\n", getpid(), getppid());
            exit(0);  // P2 terminates immediately
        } else {
            // Step 4: P1 waits for P2 to terminate
            int status;
            waitpid(p2, &status, 0);  // Wait for P2's termination
            printf("P2 terminated with status: %d\n", WEXITSTATUS(status));
        }
        exit(0);  // P1 terminates
    } else {
        // Step 5: Parent (P) waits for P1 to terminate
        int status;
        waitpid(p1, &status, 0);  // Wait for P1's termination
        printf("P1 terminated with status: %d\n", WEXITSTATUS(status));
    }

    return 0;  // Parent process exits
}
