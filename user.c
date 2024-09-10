#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        return 1;
    }

    int iterations = atoi(argv[1]);  // Convert the number of iterations from string to integer
    if (iterations <= 0) {
        fprintf(stderr, "Error: Iterations must be a positive integer\n");
        return 1;
    }

    for (int i = 0; i < iterations; i++) {
        printf("USER PID: %d, PPID: %d, Iteration: %d before sleeping\n", getpid(), getppid(), i + 1);
        sleep(1);  // Sleep for one second
        printf("USER PID: %d, PPID: %d, Iteration: %d after sleeping\n", getpid(), getppid(), i + 1);
    }

    return 0;
}
