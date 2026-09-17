#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child prints hello, sleeps 2s, exits with code 7
        printf("Hello from child (PID: %d, PPID: %d)\n", getpid(), getppid());
        sleep(2);
        _exit(7);
    }

    // Parent waits and reports child exit code
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("child %d exited with status %d\n", pid, WEXITSTATUS(status));
    }

    return 0;
}
