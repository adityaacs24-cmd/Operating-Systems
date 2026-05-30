#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 50

int disk[DISK_SIZE] = {0};  // 0 = Free, 1 = Allocated

void resetDisk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = 0;
    }

    disk[2] = 1;
    disk[5] = 1;
    disk[12] = 1;
    disk[30] = 1;
}

// a) Sequential Allocation
// Files are stored in contiguous (adjacent) blocks.
void sequentialAllocation(int fileSize) {
    int startBlock, i, j;
    printf("\n--- Sequential Allocation ---\n");
    printf("Enter starting block: ");
    scanf("%d", &startBlock);

    // Check if there is enough contiguous space
    int canAllocate = 1;
    if (startBlock + fileSize > DISK_SIZE) {
        canAllocate = 0;
    } else {
        for (i = startBlock; i < startBlock + fileSize; i++) {
            if (disk[i] == 1) {
                canAllocate = 0;
                break;
            }
        }
    }

    if (canAllocate) {
        printf("File allocated to blocks: ");
        for (i = startBlock; i < startBlock + fileSize; i++) {
            disk[i] = 1;
            printf("%d ", i);
        }
        printf("\nSuccessfully allocated!\n");
    } else {
        printf("Error: Not enough contiguous space starting from block %d.\n", startBlock);
    }
}

// b) Indexed Allocation
// A single "index block" points to all the other blocks allocated for the file.
void indexedAllocation(int fileSize) {
    int indexBlock;
    printf("\n--- Indexed Allocation ---\n");
    printf("Enter the Index Block number: ");
    scanf("%d", &indexBlock);

    if (disk[indexBlock] == 1) {
        printf("Error: Index block %d is already occupied.\n", indexBlock);
        return;
    }

    disk[indexBlock] = 1;  // Allocate the index block itself
    int allocatedBlocks[DISK_SIZE];
    int count = 0;

    // Find any free blocks scattered across the disk
    for (int i = 0; i < DISK_SIZE && count < fileSize; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            allocatedBlocks[count] = i;
            count++;
        }
    }

    if (count == fileSize) {
        printf("Index Block %d points to: ", indexBlock);
        for (int i = 0; i < fileSize; i++) {
            printf("%d ", allocatedBlocks[i]);
        }
        printf("\nSuccessfully allocated!\n");
    } else {
        printf("Error: Disk is too full to allocate %d blocks.\n", fileSize);
    }
}

// c) Linked Allocation
// Each block contains a pointer to the next block (like a Linked List).
void linkedAllocation(int fileSize) {
    printf("\n--- Linked Allocation ---\n");
    int count = 0;
    int lastBlock = -1;

    printf("File allocation path: ");
    for (int i = 0; i < DISK_SIZE && count < fileSize; i++) {
        if (disk[i] == 0) {
            disk[i] = 1;
            if (lastBlock != -1) {
                printf("%d -> ", lastBlock);
            }
            lastBlock = i;
            count++;
        }
    }

    if (count == fileSize) {
        printf("%d (End of File)\nSuccessfully allocated!\n", lastBlock);
    } else {
        printf("\nError: Disk out of space.\n");
    }
}

int main() {
    int choice, fileSize;

    while (1) {
        resetDisk();  // Clean slate for each run
        printf("\n=================================");
        printf("\nFILE ALLOCATION STRATEGIES");
        printf("\n=================================");
        printf("\n1. Sequential");
        printf("\n2. Indexed");
        printf("\n3. Linked");
        printf("\n4. Exit");
        printf("\nEnter choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4)
            break;
        if (choice < 1 || choice > 4) {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        printf("Enter file size (number of blocks): ");
        scanf("%d", &fileSize);

        switch (choice) {
            case 1:
                sequentialAllocation(fileSize);
                break;
            case 2:
                indexedAllocation(fileSize);
                break;
            case 3:
                linkedAllocation(fileSize);
                break;
        }
    }
    return 0;
}

// efficiency order:
// 1. Sequential (Best for large files, but can cause fragmentation)
// 2. Linked (Good for files that grow/shrink, but slower access due to pointers)
// 3. Indexed (Good for random access, but can waste space if index block is large and file is small)