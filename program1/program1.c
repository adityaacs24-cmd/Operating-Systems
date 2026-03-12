#include<stdio.h>

typedef struct
{
    int at, bt, ct, tat, wt;
    int done, remaining_bt;
} Process;

void fcfs(Process p[], int n)
{
    int cp = 0, curr_time = 0;

    for(int i = 0; i < n; i++)
        p[i].done = 0;

    while(cp != n)
    {
        int smallest_at = 1e9, idx = -1;

        for(int i = 0; i < n; i++)
        {
            if(p[i].at < smallest_at && !p[i].done && p[i].at <= curr_time)
            {
                smallest_at = p[i].at;
                idx = i;
            }
        }

        if (idx == -1)
        {
            curr_time++;
            continue;
        }

        curr_time += p[idx].bt;
        p[idx].ct = curr_time;
        p[idx].done = 1;
        cp++;
    }
}

void sjf(Process p[], int n)
{
    int cp = 0, curr_time = 0;

    for(int i = 0; i < n; i++)
    {
        p[i].done = 0;
    }

    while (cp != n)
    {
        int smallest_bt = 1e9, idx = -1;

        for(int i = 0; i < n; i++)
        {
            if(!p[i].done && p[i].at <= curr_time && p[i].bt <= smallest_bt)
            {
                if(p[i].bt == smallest_bt && p[i].at > p[idx].at)
                {
                    continue;
                }
                
                smallest_bt = p[i].bt;
                idx = i;
            }
        }

        if(idx == -1)
        {
            curr_time++;
            continue;
        }

        curr_time += p[idx].bt;
        p[idx].ct = curr_time;
        p[idx].done = 1;
        cp++;
    }
}

void srtf(Process p[], int n){
    int cp = 0, curr_time = 0;

    for(int i = 0; i < n; i++){
        p[i].remaining_bt = p[i].bt;
    }

    while(cp != n){
        int smallest_rt = 1e9, idx = -1;

        for(int i = 0; i < n; i++){
            if(p[i].at <= curr_time && p[i].remaining_bt > 0 && p[i].remaining_bt <= smallest_rt){
                if(p[i].remaining_bt == smallest_rt && p[i].at > p[idx].at)
                {
                    continue;
                }
                
                smallest_rt = p[i].remaining_bt;
                idx = i;
            }
        }

        if(idx == -1){
            curr_time++;
            continue;
        }

        p[idx].remaining_bt--;
        curr_time++;

        if(p[idx].remaining_bt == 0){
            p[idx].ct = curr_time;
            cp++;
        }
    }
}

void calc_avg(Process p[], int n, float *avg_tat, float* avg_wt)
{
    int tot_tat = 0, tot_wt = 0;

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        tot_tat += p[i].tat;
        tot_wt += p[i].wt;
    }

    *avg_tat = (float)tot_tat / n;
    *avg_wt = (float)tot_wt / n;
}

int main()
{
    float avg_tat, avg_wt;

    Process p[5];
    p[0].at = 2;
    p[0].bt = 1;
    p[1].at = 1;
    p[1].bt = 5;
    p[2].at = 4;
    p[2].bt = 1;
    p[3].at = 0;
    p[3].bt = 6;
    p[4].at = 2;
    p[4].bt = 3;

    // fcfs(p, 5);
    // sjf(p, 5);
    srtf(p, 5);
    calc_avg(p, 5, &avg_tat, &avg_wt);

    printf("Avg TAT: %.2f\n", avg_tat);
    printf("Avg WT: %.2f\n", avg_wt);
}

