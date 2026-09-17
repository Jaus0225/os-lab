#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_task(int task_id) {
    printf("[task %d] started by PID %d\n", task_id, getpid());
    // Simulate varying workload
    sleep(1 + (task_id % 2));
    printf("[task %d] finished by PID %d\n", task_id, getpid());
    _exit(0);
}

int main(int argc, char *argv[]) {
    int total_tasks = 8;
    int max_concurrent = 3;

    if (argc >= 2) total_tasks = atoi(argv[1]);
    if (argc >= 3) max_concurrent = atoi(argv[2]);

    printf("Starting pool: %d tasks, max %d concurrent\n", total_tasks, max_concurrent);

    int active = 0;
    int tasks_launched = 0;

    while (tasks_launched < total_tasks) {
        // If pool is saturated, wait for one worker to exit
        if (active >= max_concurrent) {
            pid_t done = wait(NULL);
            if (done > 0) {
                active--;
            }
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            run_task(tasks_launched);
        } else {
            active++;
            tasks_launched++;
        }
    }

    // Drain remaining active workers
    while (active > 0) {
        pid_t done = wait(NULL);
        if (done > 0) {
            active--;
        }
    }

    printf("All %d tasks completed.\n", total_tasks);
    return 0;
}
