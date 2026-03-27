#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Process
{
    int pid;
    int burst;
    int period;
    int deadline; 
    int remaining;
    int current_deadline;
    int tickets; 
};

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    return (a * b) / gcd(a, b);
}

// 1. Rate Monotonic Scheduling (RMS)
void runRMS(struct Process p[], int n, int hyperPeriod)
{
    printf("\n--- Running Rate Monotonic Scheduling ---\n");

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].period > p[j + 1].period)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int t = 0; t < hyperPeriod; t++)
    {
        int chosen = -1;
        for (int i = 0; i < n; i++)
        {
            if (t % p[i].period == 0)
                p[i].remaining = p[i].burst;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining > 0)
            {
                chosen = i;
                break;
            }
        }
        if (chosen != -1)
        {
            printf("Time %d: P%d\n", t, p[chosen].pid);
            p[chosen].remaining--;
        }
        else
            printf("Time %d: Idle\n", t);
    }
}

// 2. Earliest Deadline First (EDF)
void runEDF(struct Process p[], int n, int hyperPeriod) {
    printf("\n--- Running Earliest Deadline First (Custom Deadlines) ---\n");
    
    // Initialize first instances
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].current_deadline = p[i].deadline; 
    }

    for (int t = 0; t < hyperPeriod; t++) {
        // Check for new arrivals/period restarts
        for (int i = 0; i < n; i++) {
            if (t > 0 && t % p[i].period == 0) {
                // Check if previous instance finished (Deadline Miss Detection)
                if (p[i].remaining > 0) {
                    printf("[!] Deadline Miss: P%d at time %d\n", p[i].pid, t);
                }
                p[i].remaining = p[i].burst;
                p[i].current_deadline = t + p[i].deadline;
            }
        }

        int chosen = -1;
        int minDeadline = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (p[i].current_deadline < minDeadline) {
                    minDeadline = p[i].current_deadline;
                    chosen = i;
                }
            }
        }

        if (chosen != -1) {
            printf("Time %dms: P%d (Abs Deadline: %d)\n", t, p[chosen].pid, p[chosen].current_deadline);
            p[chosen].remaining--;
        } else {
            printf("Time %dms: Idle\n", t);
        }
    }
}

void runProportionalShare(struct Process p[], int n, int totalTime)
{
    printf("\n--- Running Proportional Share (Lottery) ---\n");
    int totalTickets = 0;
    for (int i = 0; i < n; i++)
    {
        printf("Enter tickets for P%d: ", p[i].pid);
        scanf("%d", &p[i].tickets);
        totalTickets += p[i].tickets;
    }

    for (int t = 0; t < totalTime; t++)
    {
        int lottery = rand() % totalTickets;
        int sum = 0, chosen = -1;

        for (int i = 0; i < n; i++)
        {
            sum += p[i].tickets;
            if (lottery < sum)
            {
                chosen = i;
                break;
            }
        }
        printf("Time %d: P%d wins lottery\n", t, p[chosen].pid);
    }
}

int main()
{
    int n, choice;
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1)
        return 1;

    struct Process p[n], temp_p[n];
    int hyperPeriod = 1;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", p[i].pid);
        printf("  Burst Time: ");
        scanf("%d", &p[i].burst);
        printf("  Period: ");
        scanf("%d", &p[i].period);
        printf("  Relative Deadline: ");
        scanf("%d", &p[i].deadline);
        
        hyperPeriod = lcm(hyperPeriod, p[i].period);
    }

    while (1)
    {
        printf("\n--- Real-Time Scheduling Simulator ---\n");
        printf("1. Rate Monotonic (RMS)\n");
        printf("2. Earliest Deadline First (EDF)\n");
        printf("3. Proportional Share (Lottery)\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        for (int i = 0; i < n; i++)
            temp_p[i] = p[i];

        switch (choice)
        {
        case 1:
            runRMS(temp_p, n, hyperPeriod);
            break;
        case 2:
            runEDF(temp_p, n, hyperPeriod);
            break;
        case 3:
            runProportionalShare(temp_p, n, hyperPeriod);
            break;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}