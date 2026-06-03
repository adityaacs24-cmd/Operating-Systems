#include <stdio.h>
#define MAX 100

void printTable(char name[], int allocation[], int processes[], int n) {
    printf("\n===== %s =====\n", name);
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void firstFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX];
    int tempBlocks[MAX];

    for (int i = 0; i < m; i++)
        tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                tempBlocks[j] -= processes[i];
                allocation[i] = j;
                break;
            }
        }
    }

    printTable("FIRST FIT", allocation, processes, n);
}

void bestFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX];
    int tempBlocks[MAX];

    for (int i = 0; i < m; i++)
        tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int best = -1;

        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                if (best == -1 || tempBlocks[j] < tempBlocks[best]) {
                    best = j;
                }
            }
        }

        if (best != -1) {
            allocation[i] = best;
            tempBlocks[best] -= processes[i];
        }
    }

    printTable("BEST FIT", allocation, processes, n);
}

void worstFit(int blocks[], int m, int processes[], int n) {
    int allocation[MAX];
    int tempBlocks[MAX];

    for (int i = 0; i < m; i++)
        tempBlocks[i] = blocks[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (tempBlocks[j] >= processes[i]) {
                if (worst == -1 || tempBlocks[j] > tempBlocks[worst]) {
                    worst = j;
                }
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            tempBlocks[worst] -= processes[i];
        }
    }

    printTable("WORST FIT", allocation, processes, n);
}

int main() {
    int m, n;
    int blocks[MAX], processes[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of memory blocks:\n");

    for (int i = 0; i < m; i++)
        scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of processes:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i]);

    firstFit(blocks, m, processes, n);
    bestFit(blocks, m, processes, n);
    worstFit(blocks, m, processes, n);

    return 0;
}