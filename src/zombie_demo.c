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
        // Child exits immediately to become a zombie
        printf("[child %d] exiting immediately\n", getpid());
        _exit(0);
    } else {
        // Parent does not call wait() right away
        printf("[parent %d] sleeping 10s... run 'ps -l' in another terminal to see child zombie state [Z]\n", getpid());
        sleep(10);

        // Reaping the child to remove the zombie
        waitpid(pid, NULL, 0);
        printf("[parent] reaped child %d; zombie cleared\n", pid);
    }

    return 0;
}
