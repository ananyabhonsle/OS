#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[100];

    if (pipe(fd) == -1) {
        printf("Pipe creation failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);

        read(fd[0], message, sizeof(message));
        printf("Child received: %s\n", message);

        close(fd[0]);
    }
    else {
        close(fd[0]);

        printf("Enter a message: ");
        fgets(message, sizeof(message), stdin);

        write(fd[1], message, sizeof(message));

        close(fd[1]);
    }

    return 0;
}
