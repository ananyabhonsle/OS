#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head;
    int request[100], visited[100];
    int total = 0;
    int min, pos, distance;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Seek sequence: %d", head);

    for (i = 0; i < n; i++) {
        min = 1000000;
        pos = -1;

        for (j = 0; j < n; j++) {
            if (visited[j] == 0) {
                distance = abs(head - request[j]);

                if (distance < min) {
                    min = distance;
                    pos = j;
                }
            }
        }

        visited[pos] = 1;
        total += min;
        head = request[pos];

        printf(" -> %d", head);
    }

    printf("\nTotal head movement = %d tracks\n", total);

    return 0;
}
