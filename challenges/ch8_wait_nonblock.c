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
        // Child simulates work by sleeping 3 seconds
        printf("[child %d] working for 3 seconds...\n", getpid());
        sleep(3);
        printf("[child %d] done\n", getpid());
        _exit(0);
    }

    // Parent polls non-blockingly
    int status;
    while (1) {
        pid_t ret = waitpid(pid, &status, WNOHANG);

        if (ret == 0) {
            printf("[parent] child still running, doing work...\n");
            usleep(500000); // 500ms
        } else if (ret == pid) {
            if (WIFEXITED(status)) {
                printf("[parent] reaped child %d with code %d\n", ret, WEXITSTATUS(status));
            }
            break;
        } else {
            perror("waitpid");
            return 1;
        }
    }

    return 0;
}
