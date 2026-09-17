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
        printf("[child %d] exiting immediately\n", getpid());
        _exit(0);
    }

    printf("[parent %d] child %d created. Sleeping 10s...\n", getpid(), pid);
    printf("--> Run 'ps -l | grep %d' or 'ps aux | grep Z' to see the zombie.\n", pid);
    
    sleep(10);

    // Reap the zombie
    waitpid(pid, NULL, 0);
    printf("[parent] reaped child %d; zombie gone\n", pid);

    return 0;
}
