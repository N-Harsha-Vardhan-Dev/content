#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 20

// FIFO page replacement function
int fifo(int pages[], int n, int frames[], int numFrames) {
    int pageFaults = 0;
    int nextReplaceIdx = 0;  // Next frame to replace in FIFO order

    // Initialize frames
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;   // -1 indicates an empty frame
    }

    // Loop through each page in the reference sequence
    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If page is not in frames, replace it
        if (!found) {
            frames[nextReplaceIdx] = pages[i];
            nextReplaceIdx = (nextReplaceIdx + 1) % numFrames;  // Circular increment
            pageFaults++;
        }

        // Display the frames after each page access
        printf("Frames after accessing page %d (FIFO): ", pages[i]);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    return pageFaults;
}

// LRU page replacement function
int lru(int pages[], int n, int frames[], int numFrames) {
    int pageFaults = 0;
    int time[MAX_FRAMES];  // Array to keep track of the time each frame was last used

    // Initialize frames and time tracking arrays
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;   // -1 indicates an empty frame
        time[i] = -1;     // Initialize time tracking for each frame
    }

    // Loop through each page in the reference sequence
    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = i;  // Update the last used time for the page
                break;
            }
        }

        // If page is not in frames, replace the LRU page
        if (!found) {
            int lruIdx = 0;

            // Find the least recently used frame by comparing time values
            for (int j = 1; j < numFrames; j++) {
                if (time[j] < time[lruIdx]) {
                    lruIdx = j;
                }
            }

            // Replace the LRU page with the current page
            frames[lruIdx] = pages[i];
            time[lruIdx] = i;  // Update the last used time for the new page
            pageFaults++;
        }

        // Display the current frames after each page access
        printf("Frames after accessing page %d (LRU): ", pages[i]);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return pageFaults;
}


int main() {
    int numPages, numFrames;
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Run FIFO algorithm
    printf("\nUsing FIFO Page Replacement Algorithm\n");
    int fifoPageFaults = fifo(pages, numPages, frames, numFrames);
    printf("\nTotal page faults (FIFO): %d\n", fifoPageFaults);

    // Run LRU algorithm
    printf("\nUsing LRU Page Replacement Algorithm\n");
    int lruPageFaults = lru(pages, numPages, frames, numFrames);
    printf("\nTotal page faults (LRU): %d\n", lruPageFaults);

    return 0;
}
