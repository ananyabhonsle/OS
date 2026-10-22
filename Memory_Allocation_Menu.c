#include <stdio.h>
 
void allocate(int original[], int nb, int process[], int np, int choice) {
    int block[nb], allocation[np], i, j, pick;
    for (i = 0; i < nb; i++) block[i] = original[i];
    for (i = 0; i < np; i++) allocation[i] = -1;
 
    for (i = 0; i < np; i++) {
        pick = -1;
        for (j = 0; j < nb; j++) {
            if (block[j] < process[i]) continue;
            if (choice == 1) { pick = j; break; }
            if (choice == 2 && (pick == -1 || block[j] < block[pick]))
                pick = j;
            if (choice == 3 && (pick == -1 || block[j] > block[pick]))
                pick = j;
        }
        if (pick != -1) {
            allocation[i] = pick;
            block[pick] -= process[i];
        }
    }
    printf("\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++) {
        printf("P%d\t%d\t", i+1, process[i]);
        if (allocation[i] == -1) printf("Not Allocated\n");
        else printf("%d\n", allocation[i]+1);
    }
    printf("Remaining block space:\n");
    for (i = 0; i < nb; i++) printf("B%d: %d\n", i+1, block[i]);
}
 
int main(void) {
    int nb, np, i, choice;
    printf("Number of blocks: "); scanf("%d", &nb);
    int original[nb];
    printf("Enter block sizes:\n");
    for (i=0; i<nb; i++) scanf("%d", &original[i]);
    printf("Number of processes: "); scanf("%d", &np);
    int process[np];
    printf("Enter process sizes:\n");
    for (i=0; i<np; i++) scanf("%d", &process[i]);
 
    do {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 3)
            allocate(original, nb, process, np, choice);
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}
