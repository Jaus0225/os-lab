#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <grep_pattern>\n", argv[0]);
        return 1;
    }

    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }

    // Child 1: runs "ls" writing to pipe
    pid_t p1 = fork();
    if (p1 < 0) {
        perror("fork 1");
        return 1;
    }
    if (p1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    // Child 2: runs "grep <pattern>" reading from pipe
    pid_t p2 = fork();
    if (p2 < 0) {
        perror("fork 2");
        return 1;
    }
    if (p2 == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("grep", "grep", argv[1], (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    // Parent closes both ends and waits
    close(fd[0]);
    close(fd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}
