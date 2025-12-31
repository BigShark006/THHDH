#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int pid;
    int bt;
    int art;
};

void findWT(struct Process p[], int n, int wt[]) {
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    int complete = 0, time = 0;
    int min = INT_MAX, shortest = 0;
    bool found = false;

    while (complete < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].art <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            time++;
            continue;
        }

        rt[shortest]--;
        min = rt[shortest] == 0 ? INT_MAX : rt[shortest];

        if (rt[shortest] == 0) {
            complete++;
            found = false;
            int finish = time + 1;
            wt[shortest] = finish - p[shortest].bt - p[shortest].art;
            if (wt[shortest] < 0) wt[shortest] = 0;
        }
        time++;
    }
}

void findTAT(struct Process p[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = p[i].bt + wt[i];
}

int main() {
    struct Process p[] = {
        {1, 6, 1},
        {2, 8, 1},
        {3, 7, 2},
        {4, 3, 3}
    };

    int n = sizeof(p) / sizeof(p[0]);
    int wt[n], tat[n];
    int twt = 0, ttat = 0;

    findWT(p, n, wt);
    findTAT(p, n, wt, tat);

    printf("PID\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].art, wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)twt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)ttat / n);
    return 0;
}
