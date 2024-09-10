#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // For fork(), exec(), and getopt()
#include <sys/wait.h>  // For wait()

int main(int argc, char *argv[]) {
    int n = 5;  // Default number of children to create
    int s = 3;  // Default number of simultaneous children allowed
    int t = 7;  // Default number of iterations for each user process
    int option;

    // Parse command-line arguments using getopt()
    while ((option = getopt(argc, argv, "n:s:t:h")) != -1) {
        switch (option) {
            case 'n':  // Number of processes
                n = atoi(optarg);  // Convert string to integer
                break;
            case 's':  // Simultaneous processes
                s = atoi(optarg);
                break;
            case 't':  // Iterations per user
                t = atoi(optarg);
                break;
            case 'h':  // Help message
                printf("Usage: oss -n [num_children] -s [simultaneous] -t [iterations]\n");
                return 0;
            default:
                printf("Unknown option\n");
                return 1;
        }
    }

    // Create child processes
    int running_children = 0;  // Track how many children are currently running
    for (int i = 0; i < n; i++) {
        if (running_children >= s) {
            // If we have max simultaneous children, wait for one to finish
            wait(NULL);
            running_children--;  // A child has finished, so decrement running count
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            // Child process: Run the 'user' program with the argument t (number of iterations)
            char iterations[10];
            sprintf(iterations, "%d", t);  // Convert t to a string for exec
            execl("./user", "user", iterations, NULL);  // Run './user t'
            perror("execl failed");  // If exec fails, print an error
            exit(1);  // Exit child process
        } else {
            // Parent process: Keep track of running children
            running_children++;
        }
    }

    // Wait for all remaining children to finish
    while (running_children > 0) {
        wait(NULL);
        running_children--;
    }

    printf("All child processes have finished.\n");
    return 0;
}
