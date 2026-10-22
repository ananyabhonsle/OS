```c
#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    if (n <= 0 || m <= 0) {
        printf("Invalid number of processes or resources.\n");
        return 1;
    }

    int alloc[n][m], max[n][m], need[n][m];
    int total[m], available[m], work[m];
    int safe_seq[n];
    bool finish[n];

    // Input Allocation Matrix
    printf("\nEnter the Allocation Matrix:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);

            if (alloc[i][j] < 0) {
                printf("Invalid allocation value.\n");
                return 1;
            }
        }
    }

    // Input Maximum Requirement Matrix
    printf("\nEnter the Max Matrix:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);

            if (max[i][j] < alloc[i][j]) {
                printf("Invalid input: Max cannot be less than Allocation.\n");
                return 1;
            }
        }
    }

    // Input Total Resources
    printf("\nEnter the total instances of each resource type:\n");

    for (int j = 0; j < m; j++) {
        scanf("%d", &total[j]);

        if (total[j] < 0) {
            printf("Invalid total resource value.\n");
            return 1;
        }
    }

    // Calculate Available and Need
    for (int j = 0; j < m; j++) {
        int allocated = 0;

        for (int i = 0; i < n; i++) {
            allocated += alloc[i][j];
        }

        if (allocated > total[j]) {
            printf("Invalid input: Allocated resources exceed total resources.\n");
            return 1;
        }

        available[j] = total[j] - allocated;
    }

    printf("\nNeed Matrix (Max - Allocation):\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    printf("\nAvailable Resources:\n");

    for (int j = 0; j < m; j++) {
        printf("%d ", available[j]);
    }

    printf("\n");

    // Initialize Work and Finish
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    // Banker's Safety Algorithm
    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (finish[i] == false) {
                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safe_seq[count] = i;
                    count++;

                    finish[i] = true;
                    found = true;
                }
            }
        }

        // No process could finish during this pass
        if (found == false) {
            break;
        }
    }

    // Display Result
    if (count == n) {
        printf("\nThe system is in a SAFE state.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safe_seq[i]);

            if (i < n - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    } else {
        printf("\nThe system is in an UNSAFE state.\n");
        printf("No safe sequence exists for the given state.\n");
    }

    return 0;
}
```
