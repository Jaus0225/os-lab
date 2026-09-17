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
        // Prepare arguments and custom environment for the worker binary
        char *args[] = {"./bin/worker", "alpha", "beta", NULL};
        char *env[] = {"MYVAR=hello", NULL};

        execve("./bin/worker", args, env);

        // execve only returns on failure
        perror("execve");
        _exit(1);
    }

    // Parent waits for worker
    waitpid(pid, NULL, 0);
    printf("Parent: worker finished execution\n");

    return 0;
}
