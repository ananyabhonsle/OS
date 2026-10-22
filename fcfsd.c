#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head;
    int request[100];
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Seek sequence: %d", head);

    for (i = 0; i < n; i++) {
        total += abs(head - request[i]);
        head = request[i];

        printf(" -> %d", head);
    }

    printf("\nTotal head movement = %d tracks\n", total);

    return 0;
}
