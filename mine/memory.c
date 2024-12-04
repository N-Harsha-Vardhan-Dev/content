#include <stdio.h>
#define MAX 100

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (no allocation)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Iterate over each process
    for (int i = 0; i < n; i++) {
        // Find the first block that can fit the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // Reduce block size after allocation
                break; // Move to the next process
            }
        }
    }

    // Output the allocation results
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (no allocation)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Iterate over each process
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;

        // Search for the smallest block that can fit the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        // Allocate the best block
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    // Output the allocation results
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (no allocation)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Iterate over each process
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        // Search for the largest block that can fit the process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        // Allocate the worst block
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    // Output the allocation results
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d not allocated\n", i + 1);
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    // Duplicate block sizes for each method
    int tempBlockSize[MAX];

    // First Fit
    for (int i = 0; i < m; i++) tempBlockSize[i] = blockSize[i];
    firstFit(tempBlockSize, m, processSize, n);

    // Best Fit
    for (int i = 0; i < m; i++) tempBlockSize[i] = blockSize[i];
    bestFit(tempBlockSize, m, processSize, n);

    // Worst Fit
    for (int i = 0; i < m; i++) tempBlockSize[i] = blockSize[i];
    worstFit(tempBlockSize, m, processSize, n);

    return 0;
}