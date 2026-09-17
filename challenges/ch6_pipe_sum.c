#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child: consumer
        close(fd[1]); // Close unused write end

        int num;
        int sum = 0;
        while (read(fd[0], &num, sizeof(int)) > 0) {
            sum += num;
        }

        close(fd[0]);
        printf("sum = %d\n", sum);
        _exit(0);
    } else {
        // Parent: producer
        close(fd[0]); // Close unused read end

        for (int i = 1; i <= 10; i++) {
            write(fd[1], &i, sizeof(int));
        }

        close(fd[1]); // Close to send EOF to child
        waitpid(pid, NULL, 0);
    }

    return 0;
}
