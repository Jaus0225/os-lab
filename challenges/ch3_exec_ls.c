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
        // Child: replace process image with 'ls -la'
        execlp("ls", "ls", "-la", (char *)NULL);

        // execlp only returns if an error occurred
        perror("execlp");
        _exit(1);
    }

    // Parent: wait for child to complete
    waitpid(pid, NULL, 0);
    printf("Parent: child finished ls -la\n");

    return 0;
}
