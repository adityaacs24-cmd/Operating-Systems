#include <stdio.h>

#define MAX 10

typedef struct {
    int pid, at, bt, rt, ct, tat, wt, queue;
} Process;

int main() {
    Process p[MAX];
    int n, i, curr_time = 0, cp = 0;
    int tq = 2;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nP%d\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Queue (1-System, 2-User): ");
        scanf("%d", &p[i].queue);
        
        p[i].rt = p[i].bt; // remaining time
    }

    printf("\nGantt Chart:\n");

    while (cp != n) {
        int found = 0;

        // --- 1. QUEUE 1: ROUND ROBIN (High Priority) ---
        for (i = 0; i < n; i++) {
            // Check if a Queue 1 process is ready to run
            if (p[i].queue == 1 && p[i].at <= curr_time && p[i].rt > 0) {
                found = 1;
                printf("P%d ", p[i].pid);

                // Run for 1 time quantum or remaining time (whichever is lower)
                int run_time = (p[i].rt > tq) ? tq : p[i].rt;
                
                curr_time += run_time;
                p[i].rt -= run_time;

                if (p[i].rt == 0) {
                    p[i].ct = curr_time;
                    cp++;
                }
                
                break; // Break to check if any other process has arrived or needs priority
            }
        }

        // --- 2. QUEUE 2: FCFS (Low Priority) ---
        // Only executes if no Queue 1 process was found ready
        if (!found) {
            int smallest_at = 1e9, idx = -1;

            // Find the FCFS candidate (lowest arrival time among ready Queue 2 processes)
            for (i = 0; i < n; i++) {
                if (p[i].queue == 2 && p[i].rt > 0 && p[i].at <= curr_time) {
                    if (p[i].at < smallest_at) {
                        smallest_at = p[i].at;
                        idx = i;
                    }
                }
            }

            if (idx != -1) {
                found = 1;
                printf("P%d ", p[idx].pid);

                // Process for exactly 1 unit of time so Queue 1 can preempt if it arrives
                curr_time++;
                p[idx].rt--;

                if (p[idx].rt == 0) {
                    p[idx].ct = curr_time;
                    cp++;
                }
            }
        }

        // --- 3. IDLE TIME ---
        if (!found) {
            curr_time++;
        }
    }

    // --- 4. METRICS PRINTING ---
    float total_tat = 0, total_wt = 0;
    printf("\n\nPID\tQ\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].queue, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT = %.2f\n", total_wt / n);

    return 0;
}