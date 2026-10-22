#include <stdio.h>
int main(void) {
    int n, i, time = 0;
    printf("Number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], done[n];
    for (i=0; i<n; i++) {
        printf("P%d Arrival Time and Burst Time: ", i+1);
        scanf("%d%d", &at[i], &bt[i]);
        done[i] = 0;
    }
 
    int completed = 0;
    while (completed < n) {
        int p = -1;
        for (i=0; i<n; i++) {
            if (!done[i] && at[i] <= time &&
                (p == -1 || bt[i] < bt[p] ||
                 (bt[i] == bt[p] && at[i] < at[p]))) p = i;
        }
        if (p == -1) {
            int next = -1;
            for (i=0; i<n; i++)
                if (!done[i] && (next == -1 || at[i] < at[next])) next = i;
            time = at[next];
            continue;
        }
        time += bt[p]; ct[p] = time; done[p] = 1; completed++;
    }
 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i=0; i<n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}
