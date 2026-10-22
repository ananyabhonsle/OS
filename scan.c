#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, disk_size, direction;
    int request[100];
    int total = 0, temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (0 for lower, 1 for higher): ");
    scanf("%d", &direction);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    printf("Seek sequence: %d", head);

    if (direction == 1) {
        for (i = 0; i < n; i++) {
            if (request[i] >= head) {
                total += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }

        if (head != disk_size - 1) {
            total += abs(head - (disk_size - 1));
            head = disk_size - 1;
            printf(" -> %d", head);
        }

        for (i = n - 1; i >= 0; i--) {
            if (request[i] < head) {
                total += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }
    else {
        for (i = n - 1; i >= 0; i--) {
            if (request[i] <= head) {
                total += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }

        if (head != 0) {
            total += head;
            head = 0;
            printf(" -> %d", head);
        }

        for (i = 0; i < n; i++) {
            if (request[i] > head) {
                total += abs(head - request[i]);
                head = request[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal head movement = %d tracks\n", total);

    return 0;
}
