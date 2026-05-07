#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    bool finish[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        bool zeroAllocation = true;

        for (int j = 0; j < m; j++) {
            if (allocation[i][j] != 0) {
                zeroAllocation = false;
                break;
            }
        }

        finish[i] = zeroAllocation;
    }

    int count = 0;

    while (1) {
        bool found = false;

        for (int i = 0; i < n; i++) {

            if (finish[i] == false) {

                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {

                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    safeSequence[count] = i;
                    count++;

                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    bool deadlock = false;

    for (int i = 0; i < n; i++) {
        if (finish[i] == false) {
            deadlock = true;
            break;
        }
    }

    if (!deadlock) {
        printf("\nNo Deadlock detected.\n");

        printf("Safe Sequence: ");
        for (int i = 0; i < count; i++) {
            printf("P%d", safeSequence[i]);

            if (i != count - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else {
        printf("\nDeadlock detected.\n");

        printf("Processes involved in deadlock: ");

        for (int i = 0; i < n; i++) {
            if (finish[i] == false) {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}