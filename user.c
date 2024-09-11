#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long iterations = strtol(argv[1], &endptr, 10);

    // Check for error like  empty string and characters left after number
    if (endptr == argv[1]) {
        fprintf(stderr, "Error: No digits were found\n");
        return EXIT_FAILURE;
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Error: Non-numeric characters present\n");
        return EXIT_FAILURE;
    }

    // Check for valid range (positive number and within int range)
    if (iterations <= 0 || iterations > INT_MAX) {
        fprintf(stderr, "Error: Iterations must be a positive integer and less than %d\n", INT_MAX);
        return EXIT_FAILURE;
    }

    // Loop iterations, safe to cast since we checked range above
    for (int i = 0; i < iterations; i++) {
        printf("USER PID: %d, PPID: %d, Iteration: %d before sleeping\n", getpid(), getppid(), i + 1);
        sleep(1);  // Sleep for one second
        printf("USER PID: %d, PPID: %d, Iteration: %d after sleeping\n", getpid(), getppid(), i + 1);
    }

    return EXIT_SUCCESS;
}
