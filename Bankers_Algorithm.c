#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    // Step 1: Input dimensions
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int total_resources[m], total_allocated[m], avail[m];

    // Step 2: Input Allocation Matrix
    printf("\nEnter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Step 3: Input Max Matrix
    printf("\nEnter the Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Step 4: Input Total Instances of Resources
    printf("\nEnter the Total Instances of each resource type:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &total_resources[j]);
        total_allocated[j] = 0; // Initialize allocation sum
    }

    // Step 5: Calculate Available Matrix (Total - Sum of Allocated)
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            total_allocated[j] += alloc[i][j];
        }
        avail[j] = total_resources[j] - total_allocated[j];
    }

    // Step 6: Calculate the Remaining Need Matrix (Max - Allocation)
    printf("\nCalculated Remaining Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Print calculated Available array for verification
    printf("\nAutomatically Calculated Available Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("%d ", avail[j]);
    }
    printf("\n\n");

    // Step 7: Safety Algorithm
    bool finish[n];
    int safe_seq[n];
    int ind = 0;
    
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    for (int k = 0; k < n; k++) {
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
                    for (int y = 0; y < m; y++) {
                        work[y] += alloc[i][y];
                    }
                    safe_seq[ind++] = i;
                    finish[i] = true;
                }
            }
        }
    }

    // Step 8: Output the Results
    bool safe = true;
    for (int i = 0; i < n; i++) {
        if (finish[i] == false) {
            safe = false;
            printf("The system is NOT in a safe state (Deadlock imminent).\n");
            break;
        }
    }

    if (safe) {
        printf("The system is in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < n - 1; i++) {
            printf("P%d -> ", safe_seq[i]);
        }
        printf("P%d\n", safe_seq[n - 1]);
    }

    return 0;
}
