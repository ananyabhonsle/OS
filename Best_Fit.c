#include <stdio.h>
 
int main(void) {
    int nb, np, i, j;
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    int block[nb];
    printf("Enter block sizes:\n");
    for (i = 0; i < nb; i++) scanf("%d", &block[i]);
 
    printf("Enter number of processes: ");
    scanf("%d", &np);
    int process[np], allocation[np];
    printf("Enter process sizes:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &process[i]);
        allocation[i] = -1;
    }
 
    for (i = 0; i < np; i++) {
        int best = -1;
        for (j = 0; j < nb; j++) {
            if (block[j] >= process[i] &&
                (best == -1 || block[j] < block[best]))
                best = j;
        }
        if (best != -1) {
            allocation[i] = best;
            block[best] -= process[i];
        }
    }
 
    printf("\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);
        if (allocation[i] == -1) printf("Not Allocated\n");
        else printf("%d\n", allocation[i] + 1);
    }
    return 0;
}
