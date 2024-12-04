#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int alloc[MAX_PROCESSES][MAX_RESOURCES], int n, int r) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int n, int r) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, alloc, n, r);

    int work[MAX_RESOURCES];
    for (int i = 0; i < r; i++)
        work[i] = avail[i];

    int finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int count = 0;

    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == r) {
                    for (int k = 0; k < r; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return 1;
}

int main() {
    int n, r;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int processes[MAX_PROCESSES];
    for (int i = 0; i < n; i++) processes[i] = i;

    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    isSafe(processes, avail, max, alloc, n, r);

    return 0;
}