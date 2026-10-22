#include <stdio.h>

int main() {
    int n, f, i, j, k;
    int pages[100], frames[20], time[20];
    int faults = 0, hits = 0, found;
    int oldest, pos, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (i = 0; i < n; i++) {
        found = 0;
        counter++;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                hits++;
                time[j] = counter;
                break;
            }
        }

        if (found == 0) {
            pos = -1;

            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                oldest = time[0];
                pos = 0;

                for (j = 1; j < f; j++) {
                    if (time[j] < oldest) {
                        oldest = time[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }

        printf("Page %d: ", pages[i]);

        for (k = 0; k < f; k++) {
            if (frames[k] == -1) {
                printf("- ");
            } else {
                printf("%d ", frames[k]);
            }
        }

        if (found == 1) {
            printf("Hit\n");
        } else {
            printf("Fault\n");
        }
    }

    printf("Total Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", hits);

    return 0;
}
