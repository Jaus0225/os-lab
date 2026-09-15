#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child: replace process image with 'ls -l'
        printf("[child] about to exec ls -l\n");
        execlp("ls", "ls", "-l", (char *)NULL);

        // If exec returns, it failed
        perror("execlp");
        _exit(1);
    } else {
        // Parent: wait for child to complete
        waitpid(pid, NULL, 0);
        printf("[parent] child finished exec\n");
    }

    return 0;
}
