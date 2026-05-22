#include <stdio.h>

int main() {
    int pages[20], frames[10];
    int n, f, i, j, k, faults;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // ---------------- FIFO ----------------
    printf("\nFIFO Page Replacement\n");

    for (i = 0; i < f; i++)
        frames[i] = -1;

    faults = 0;
    int index = 0;

    for (i = 0; i < n; i++) {

        int found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        // for (j = 0; j < f; j++)
            // printf("%d ", frames[j]);

        // printf("\n");
    }

    printf("Page Faults = %d\n", faults);

    // ---------------- LRU ----------------
    printf("\nLRU Page Replacement\n");

    int time[10], count = 0;

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    faults = 0;

    for (i = 0; i < n; i++) {

        int found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if (!found) {

            int min = 0;

            for (j = 1; j < f; j++) {
                if (time[j] < time[min])
                    min = j;
            }

            frames[min] = pages[i];

            count++;
            time[min] = count;

            faults++;
        }

        // for (j = 0; j < f; j++)
            // printf("%d ", frames[j]);

        // printf("\n");
    }

    printf("Page Faults = %d\n", faults);

    // ---------------- Optimal ----------------
    printf("\nOptimal Page Replacement\n");

    for (i = 0; i < f; i++)
        frames[i] = -1;

    faults = 0;

    for (i = 0; i < n; i++) {

        int found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {

            int pos = -1;

            // Empty frame
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Find farthest page
            if (pos == -1) {

                int farthest = -1;

                for (j = 0; j < f; j++) {

                    int nextUse = 999;

                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            faults++;
        }

        // for (j = 0; j < f; j++)
            // printf("%d ", frames[j]);

        // printf("\n");
    }

    printf("Page Faults = %d\n", faults);

    return 0;
}