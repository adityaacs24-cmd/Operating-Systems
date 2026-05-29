#include <stdio.h>
#include <stdlib.h>

#define MAX 8

// Helper function to sort the request array (used in SCAN, SSTF, C-LOOK)
void sortArray(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// a) First Come First Served (FCFS)
// Processes requests exactly in the order they arrive.
void fcfs(int req[], int n, int head) {
    int totalMovement = 0;
    int current = head;

    printf("\n--- FCFS Scheduling ---\nPath: %d", head);
    for (int i = 0; i < n; i++) {
        totalMovement += abs(req[i] - current);
        current = req[i];
        printf(" -> %d", current);
    }
    printf("\nTotal Head Movement: %d tracks\n", totalMovement);
}

// b) Shortest Seek Time First (SSTF)
// Always services the closest track to the current head position.
void sstf(int req[], int n, int head) {
    int totalMovement = 0;
    int current = head;
    int visited[MAX] = {0};  // Tracks processed requests

    printf("\n--- SSTF Scheduling ---\nPath: %d", head);
    for (int i = 0; i < n; i++) {
        int minDistance = 9999;
        int index = -1;

        // Find the unvisited track with the shortest distance
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(req[j] - current) < minDistance) {
                minDistance = abs(req[j] - current);
                index = j;
            }
        }

        visited[index] = 1;
        totalMovement += minDistance;
        current = req[index];
        printf(" -> %d", current);
    }
    printf("\nTotal Head Movement: %d tracks\n", totalMovement);
}

// c) SCAN (Elevator Algorithm)
// Moves completely to one end of the disk (0), then reverses direction.
void scan(int req[], int n, int head) {
    int totalMovement = 0;
    int current = head;
    int sorted[MAX];

    // Copy and sort the requests
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sortArray(sorted, n);

    printf("\n--- SCAN Scheduling (Moving Down to 0) ---\nPath: %d", head);

    // Step 1: Move down towards 0, servicing smaller tracks
    for (int i = n - 1; i >= 0; i--) {
        if (sorted[i] <= head) {
            totalMovement += abs(sorted[i] - current);
            current = sorted[i];
            printf(" -> %d", current);
        }
    }

    // Hit the disk boundary at 0
    totalMovement += abs(0 - current);
    current = 0;
    printf(" -> 0");

    // Step 2: Reverse direction and service larger tracks
    for (int i = 0; i < n; i++) {
        if (sorted[i] > head) {
            totalMovement += abs(sorted[i] - current);
            current = sorted[i];
            printf(" -> %d", current);
        }
    }
    printf("\nTotal Head Movement: %d tracks\n", totalMovement);
}

// d) Circular LOOK (C-LOOK)
// Goes only as far as the last request in one direction, wraps to the start, but doesn't touch 0 or Max.
void clook(int req[], int n, int head) {
    int totalMovement = 0;
    int current = head;
    int sorted[MAX];

    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sortArray(sorted, n);

    printf("\n--- C-LOOK Scheduling (Moving Up) ---\nPath: %d", head);

    // Step 1: Service everything larger than head moving up
    for (int i = 0; i < n; i++) {
        if (sorted[i] >= head) {
            totalMovement += abs(sorted[i] - current);
            current = sorted[i];
            printf(" -> %d", current);
        }
    }

    // Step 2: Circular wrap-around directly to the absolute lowest requested track
    for (int i = 0; i < n; i++) {
        if (sorted[i] < head) {
            totalMovement += abs(sorted[i] - current);
            current = sorted[i];
            printf(" -> %d", current);
        }
    }
    printf("\nTotal Head Movement: %d tracks\n", totalMovement);
}

int main() {
    // Standard academic example queue
    int requests[MAX] = {98, 183, 37, 122, 14, 124, 65, 67};
    int initialHead = 53;

    printf("Disk Request Queue: ");
    for (int i = 0; i < MAX; i++)
        printf("%d ", requests[i]);
    printf("\nInitial Head Position: %d\n", initialHead);

    fcfs(requests, MAX, initialHead);
    sstf(requests, MAX, initialHead);
    scan(requests, MAX, initialHead);
    clook(requests, MAX, initialHead);

    return 0;
}

//efficiency order:
// 1. SSTF (Best for minimizing head movement, but can cause starvation)
// 2. SCAN (Good for large queues, but can lead to longer wait times for requests at the opposite end)
// 3. C-LOOK (Similar to SCAN but more efficient for large queues with clustered requests)
// 4. FCFS (Simple but can lead to long wait times and high head movement