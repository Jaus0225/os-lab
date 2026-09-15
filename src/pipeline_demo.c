#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // First child: runs "ls" and writes output to pipe
    pid_t p1 = fork();
    if (p1 < 0) {
        perror("fork 1");
        return 1;
    }

    if (p1 == 0) {
        close(fd[0]);               // Unused read end
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
        close(fd[1]);               // Close duplicate fd
        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    // Second child: runs "grep .c" reading input from pipe
    pid_t p2 = fork();
    if (p2 < 0) {
        perror("fork 2");
        return 1;
    }

    if (p2 == 0) {
        close(fd[1]);              // Unused write end
        dup2(fd[0], STDIN_FILENO); // Redirect stdin to read end of pipe
        close(fd[0]);              // Close duplicate fd
        execlp("grep", "grep", ".c", (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    // Parent: must close both ends so child 2 sees EOF, then wait for both
    close(fd[0]);
    close(fd[1]);

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 0;
}
