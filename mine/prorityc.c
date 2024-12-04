#include <stdio.h>
#include <limits.h>

// Function to swap two variables
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time and priority
void sort_by_arrival_time_and_priority(int n, int arrival[], int burst[], int priority[], int index[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j] || (arrival[i] == arrival[j] && priority[i] > priority[j])) {
                swap(&arrival[i], &arrival[j]);
                swap(&burst[i], &burst[j]);
                swap(&priority[i], &priority[j]);
                swap(&index[i], &index[j]);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    int burst_time[n], priority[n], arrival_time[n], index[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time, Priority, and Arrival Time for Process %d: ", i + 1);
        scanf("%d %d %d", &burst_time[i], &priority[i], &arrival_time[i]);
        index[i] = i + 1;  // Process ID
    }

    sort_by_arrival_time_and_priority(n, arrival_time, burst_time, priority, index);

    int t = 0;  // Current time
    int total_wait_time = 0, total_turnaround_time = 0;
    int completed[n];

    for (int i = 0; i < n; i++) completed[i] = 0;

    printf("\nProcess Execution Details:\n");
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int min_priority = INT_MAX;
        int process_to_execute = -1;

        for (int j = 0; j < n; j++) {
            if (!completed[j] && arrival_time[j] <= t && priority[j] < min_priority) {
                min_priority = priority[j];
                process_to_execute = j;
            }
        }

        if (process_to_execute != -1) {
            completed[process_to_execute] = 1;
            int wait_time = t - arrival_time[process_to_execute];
            t += burst_time[process_to_execute];
            int turnaround_time = t - arrival_time[process_to_execute];

            total_wait_time += wait_time;
            total_turnaround_time += turnaround_time;

            printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                   index[process_to_execute], burst_time[process_to_execute], priority[process_to_execute], wait_time, turnaround_time);
        } else {
            t++;  // Increment time if no process is ready
        }
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wait_time / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround_time / n);

    return 0;
}
