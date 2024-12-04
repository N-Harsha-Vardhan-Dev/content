#include <stdio.h>
#define MAX 100

void pagingTechnique(int pageSize, int memorySize, int numProcesses, int processSizes[]) {
    int numFrames = memorySize / pageSize;
    int pageTable[MAX][MAX]; // Stores frame allocation for each process's pages
    int currentFrame = 0, i, j;

    printf("\nPaging Technique Simulation:\n");
    printf("Physical Memory Size: %d, Page Size: %d, Number of Frames: %d\n\n", memorySize, pageSize, numFrames);

    for (i = 0; i < numProcesses; i++) {
        int numPages = (processSizes[i] + pageSize - 1) / pageSize; // Rounding up
        printf("Process %d: Size = %d, Pages Required = %d\n", i + 1, processSizes[i], numPages);

        if (currentFrame + numPages > numFrames) {
            printf("Not enough memory to allocate process %d.\n", i + 1);
            continue;
        }

        printf("Page Table for Process %d:\n", i + 1);
        for (j = 0; j < numPages; j++) {
            pageTable[i][j] = currentFrame; // Assign current frame
            printf("  Page %d -> Frame %d\n", j, currentFrame);
            currentFrame++;
        }
    }
}

int main() {
    int memorySize, pageSize, numProcesses, processSizes[MAX];
    int i;

    // Input memory and page size
    printf("Enter physical memory size: ");
    scanf("%d", &memorySize);
    printf("Enter page size: ");
    scanf("%d", &pageSize);

    // Input process information
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter sizes of processes:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("  Process %d: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    // Call the paging simulation function
    pagingTechnique(pageSize, memorySize, numProcesses, processSizes);

    return 0;
}
