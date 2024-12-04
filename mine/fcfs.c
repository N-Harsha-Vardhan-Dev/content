#include <stdio.h>

int main() {
    int pid[15];      // Process IDs
    int bt[15];       // Burst times
    int at[15];       // Arrival times
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process ID of all the processes: ");
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

    int ct[15];       // Completion times
    int tat[15];      // Turnaround times
    int wt[15];       // Waiting times
    int time = 0;
    float total_wt = 0, total_tat = 0;

    // Sort processes by arrival time if not sorted
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                // Swap process IDs
                int temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;

                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculate completion, turnaround, and waiting times
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i]; // Start time matches arrival if CPU was idle
        }

        ct[i] = time + bt[i];             // Completion time
        tat[i] = ct[i] - at[i];           // Turnaround time
        wt[i] = tat[i] - bt[i];           // Waiting time

        time += bt[i];                    // Move time forward

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and turnaround time
    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    printf("Average waiting time = %.2f\n", avg_wt);
    printf("Average turnaround time = %.2f\n", avg_tat);

    return 0;
}
