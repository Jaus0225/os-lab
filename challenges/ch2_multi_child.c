#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num_children>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            // Child: print index and exit with index + 1
            printf("Child %d (PID: %d)\n", i, getpid());
            _exit(i + 1);
        }
    }

    // Parent collects all children
    int status;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Parent collected child PID %d with exit code %d\n", wpid, WEXITSTATUS(status));
        }
    }

    return 0;
}
