#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // Child A: uses execlp (variadic arguments, searches PATH)
    pid_t p1 = fork();
    if (p1 < 0) {
        perror("fork 1");
        return 1;
    }
    if (p1 == 0) {
        execlp("echo", "echo", "one", "two", (char *)NULL);
        perror("execlp");
        _exit(1);
    }
    waitpid(p1, NULL, 0);

    // Child B: uses execvp (array of arguments, searches PATH)
    pid_t p2 = fork();
    if (p2 < 0) {
        perror("fork 2");
        return 1;
    }
    if (p2 == 0) {
        char *args[] = {"echo", "one", "two", NULL};
        execvp("echo", args);
        perror("execvp");
        _exit(1);
    }
    waitpid(p2, NULL, 0);

    return 0;
}
