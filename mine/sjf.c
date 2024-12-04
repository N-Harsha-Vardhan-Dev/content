#include <stdio.h>

int main() {
    int pid[15], bt[15], at[15], ct[15], tat[15], wt[15];
    int n, completed[15] = {0}; // `completed` array to track completed processes
    int total_tat = 0, total_wt = 0;
    int currentTime = 0, completedCount = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process IDs of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pid[i]);
    }

    printf("Enter arrival time of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter burst time of all the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    // Main loop to process all jobs in SJF non-preemptive manner
    while (completedCount < n) {
        int shortestJob = -1;
        int shortestBT = __INT_MAX__; // Use maximum int value to find the minimum

        // Find the process with the shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && completed[i] == 0) { // Process has arrived and is not completed
                if (bt[i] < shortestBT) {
                    shortestBT = bt[i];
                    shortestJob = i;
                }
            }
        }

        if (shortestJob == -1) {
            // No process is available at the current time, so increment time
            currentTime++;
            continue;
        }

        // Process the shortest job found
        completed[shortestJob] = 1;         // Mark it as completed
        currentTime += bt[shortestJob];     // Move current time by burst time of this process
        ct[shortestJob] = currentTime;      // Completion time of this process
        tat[shortestJob] = ct[shortestJob] - at[shortestJob]; // Turnaround time
        wt[shortestJob] = tat[shortestJob] - bt[shortestJob]; // Waiting time

        total_tat += tat[shortestJob];
        total_wt += wt[shortestJob];
        completedCount++;
    }

    // Display process information
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and turnaround time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average waiting time = %.2f\n", avg_wt);
    printf("Average turnaround time = %.2f\n", avg_tat);

    return 0;
}
