#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CHILDREN 10  // Maximum number of child processes

int main(int argc, char *argv[]) {
    int n = 5;  // Total number of children to create
    int s = 3;  // Maximum number of simultaneous children
    int t = 7;  // Iterations for each child
    int option;

    // Parse command-line arguments

    while ((option = getopt(argc, argv, "n:s:t:h")) != -1) {
        switch (option) {
            case 'n':
                n = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 't':
                t = atoi(optarg);
                break;
            case 'h':
                printf("Usage: %s -n [num_children] -s [simultaneous] -t [iterations]\n", argv[0]);
                return EXIT_SUCCESS;
            default:
                fprintf(stderr, "Unknown option\n");
                return EXIT_FAILURE;
        }
    }

    pid_t child_pids[MAX_CHILDREN] = {0};
    int num_children = 0;
    int total_launched = 0;
// outer and inner loop to manage the creation and lifecycle of child

    while (total_launched < n || num_children > 0) {
        while (num_children < s && total_launched < n) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                char iterations[10];
                sprintf(iterations, "%d", t);
                execl("./user", "user", iterations, NULL);
                perror("execl failed");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // Parent process
                child_pids[num_children++] = pid;
                total_launched++;
            }
        }

        // Wait for any child to finish
        int status;
        pid_t finished_pid = wait(&status);
        if (finished_pid == -1) {
            perror("wait failed");
            exit(EXIT_FAILURE);
        }

        // Remove the finished child from the list
        for (int i = 0; i < num_children; i++) {
            if (child_pids[i] == finished_pid) {
                child_pids[i] = child_pids[num_children - 1];  // Replace finished child with the last in the list
                num_children--;  // Decrease the count of running children
                break;
            }
        }
    }

    printf("All child processes have finished.\n");
    return EXIT_SUCCESS;
}
