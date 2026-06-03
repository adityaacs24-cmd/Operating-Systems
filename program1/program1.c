#include <stdio.h>

typedef struct {
    int at, bt, ct, tat, wt, in_queue;
    int done, remaining_bt, priority;
} Process;

void fcfs(Process p[], int n) {
    int cp = 0, curr_time = 0;

    for (int i = 0; i < n; i++)
        p[i].done = 0;

    while (cp != n) {
        int smallest_at = 1e9, idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at < smallest_at && !p[i].done && p[i].at <= curr_time) {
                smallest_at = p[i].at;
                idx = i;
            }
        }

        if (idx == -1) {
            curr_time++;
            continue;
        }

        curr_time += p[idx].bt;
        p[idx].ct = curr_time;
        p[idx].done = 1;
        cp++;
    }
}

void sjf(Process p[], int n) {
    int cp = 0, curr_time = 0;

    for (int i = 0; i < n; i++) {
        p[i].done = 0;
    }

    while (cp != n) {
        int smallest_bt = 1e9, idx = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= curr_time && p[i].bt <= smallest_bt) {
                if (p[i].bt == smallest_bt && p[i].at > p[idx].at) {
                    continue;
                }

                smallest_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            curr_time++;
            continue;
        }

        curr_time += p[idx].bt;
        p[idx].ct = curr_time;
        p[idx].done = 1;
        cp++;
    }
}

void srtf(Process p[], int n) {
    int cp = 0, curr_time = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
    }

    while (cp != n) {
        int smallest_rt = 1e9, idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= curr_time && p[i].remaining_bt > 0 && p[i].remaining_bt <= smallest_rt) {
                if (p[i].remaining_bt == smallest_rt && p[i].at > p[idx].at) {
                    continue;
                }

                smallest_rt = p[i].remaining_bt;
                idx = i;
            }
        }

        if (idx == -1) {
            curr_time++;
            continue;
        }

        p[idx].remaining_bt--;
        curr_time++;

        if (p[idx].remaining_bt == 0) {
            p[idx].ct = curr_time;
            cp++;
        }
    }
}

void priority_np(Process p[], int n) {
    int cp = 0, curr_time = 0;

    for (int i = 0; i < n; i++) {
        p[i].done = 0;
    }

    while (cp != n) {
        int highest_pr = 1e9, idx = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= curr_time && p[i].priority <= highest_pr) {
                if (p[i].priority == highest_pr && p[i].at > p[idx].at) {
                    continue;
                }

                highest_pr = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            curr_time++;
            continue;
        }

        curr_time += p[idx].bt;
        p[idx].ct = curr_time;
        p[idx].done = 1;
        cp++;
    }
}

void priority_p(Process p[], int n) {
    int cp = 0, curr_time = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
    }

    while (cp != n) {
        int highest_pr = 1e9, idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= curr_time && p[i].remaining_bt > 0 && p[i].priority <= highest_pr) {
                if (p[i].priority == highest_pr && p[i].at > p[idx].at) {
                    continue;
                }

                highest_pr = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            curr_time++;
            continue;
        }

        p[idx].remaining_bt--;
        curr_time++;

        if (p[idx].remaining_bt == 0) {
            p[idx].ct = curr_time;
            cp++;
        }
    }
}

void round_robin(Process p[], int n, int tq) {
    int cp = 0, curr_time = 0;

    // An array to serve as our FIFO queue storing process indices
    // MAX_Q needs to be large enough to handle processes re-entering multiple times
    int queue[100];
    int front = 0, rear = 0;

    // Initialize remaining burst time and queue tracking flags
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].in_queue = 0;
    }

    while (cp != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= curr_time && !p[i].in_queue && p[i].remaining_bt > 0) {
                queue[rear++] = i;
                p[i].in_queue = 1;
            }
        }

        // If the queue is not empty, process the next item
        if (front < rear) {
            int idx = queue[front++];  // Dequeue

            printf("P%d ", idx + 1);

            // Determine how long to run (either the full quantum or whatever is left)
            int run_time = (p[idx].remaining_bt > tq) ? tq : p[idx].remaining_bt;

            // Execute step-by-step (1 unit at a time) to catch mid-quantum arrivals
            for (int t = 0; t < run_time; t++) {
                curr_time++;
                p[idx].remaining_bt--;

                // Check for newly arrived processes during this time tick
                for (int i = 0; i < n; i++) {
                    if (p[i].at <= curr_time && !p[i].in_queue && p[i].remaining_bt > 0) {
                        queue[rear++] = i;  // Enqueue new arrival
                        p[i].in_queue = 1;
                    }
                }
            }

            p[idx].in_queue = 0;

            // Check if the current process finished or needs to go to the back of the queue
            if (p[idx].remaining_bt == 0) {
                p[idx].ct = curr_time;
                cp++;
            } else {
                queue[rear++] = idx;  // Enqueue back to the rear
                p[idx].in_queue = 1;
            }
        }
        // If the queue is empty, the CPU is idling
        else {
            curr_time++;
        }
    }
}

void calc_avg(Process p[], int n, float* avg_tat, float* avg_wt) {
    int tot_tat = 0, tot_wt = 0;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        tot_tat += p[i].tat;
        tot_wt += p[i].wt;
    }

    *avg_tat = (float)tot_tat / n;
    *avg_wt = (float)tot_wt / n;
}

int main() {
    float avg_tat, avg_wt;

    Process p[6];
    p[0].at = 0;
    p[0].bt = 4;
    p[0].priority = 5;
    p[1].at = 1;
    p[1].bt = 5;
    p[1].priority = 3;
    p[2].at = 2;
    p[2].bt = 2;
    p[2].priority = 2;
    p[3].at = 3;
    p[3].bt = 1;
    p[3].priority = 4;
    p[4].at = 4;
    p[4].bt = 6;
    p[4].priority = 1;
    p[5].at = 6;
    p[5].bt = 3;
    p[5].priority = 1;

    // fcfs(p, 5);
    // sjf(p, 5);
    // srtf(p, 5);
    // priority_np(p, 5);
    round_robin(p, 6, 2);
    printf("\n\n");
    calc_avg(p, 6, &avg_tat, &avg_wt);

    printf("Avg TAT: %.2f\n", avg_tat);
    printf("Avg WT: %.2f\n", avg_wt);
}
