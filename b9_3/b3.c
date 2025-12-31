#include <stdio.h>
#include <stdbool.h>

// Tính Waiting Time
void findWT(int processes[], int n, int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0;

    while (true)
    {
        bool done = true;

        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;

                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if (done)
            break;
    }
}

// Tính Turn Around Time
void findTAT(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

// In kết quả + trung bình
void findAT(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWT(processes, n, bt, wt, quantum);
    findTAT(processes, n, bt, wt, tat);

    printf("PID\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];

        printf("%d\t%d\t%d\t%d\n",
               processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",
           (float)total_wt / n);
    printf("\nAverage Turn Around Time = %.2f\n",
           (float)total_tat / n);
}

int main()
{
    int processes[] = {1, 2, 3};
    int burst_time[] = {10, 5, 8};
    int quantum = 2;

    int n = sizeof(processes) / sizeof(processes[0]);

    findAT(processes, n, burst_time, quantum);

    return 0;
}
