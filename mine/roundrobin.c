#include <stdio.h>

void roundRobin(int n, int arrivalTime[], int burstTime[], int timeQuantum) {
    int remainingTime[n], waitTime[n], turnAroundTime[n];
    int completed = 0, currentTime = 0;
    int i, flag = 0;

    // Initialize remaining times and waiting times
    for (i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        waitTime[i] = 0;
    }

    // Start processing
    while (completed < n) {
        flag = 0; // Flag to check if a process was executed in this iteration
        for (i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0) {
                flag = 1;
                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;
                    completed++;

                    // Calculate turnaround and waiting times
                    turnAroundTime[i] = currentTime - arrivalTime[i];
                    waitTime[i] = turnAroundTime[i] - burstTime[i];
                }
            }
        }

        // If no process is executed, move the time forward
        if (flag == 0) {
            currentTime++;
        }
    }

    // Output results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, arrivalTime[i], burstTime[i], waitTime[i], turnAroundTime[i]);
    }

    // Calculate average waiting and turnaround times
    float totalWaitTime = 0, totalTurnAroundTime = 0;
    for (i = 0; i < n; i++) {
        totalWaitTime += waitTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n, i, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrivalTime[n], burstTime[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(n, arrivalTime, burstTime, timeQuantum);

    return 0;
}
