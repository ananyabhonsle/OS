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
 
    for (i=0; i<n; i++) {
        int p = -1, j;
        for (j=0; j<n; j++)
            if (!done[j] && (p == -1 || at[j] < at[p])) p = j;
        if (time < at[p]) time = at[p]; /* CPU idle */
        time += bt[p];
        ct[p] = time;
        done[p] = 1;
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
