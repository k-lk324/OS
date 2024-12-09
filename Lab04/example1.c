example2.c                                                                                          0000664 0002422 0002424 00000000533 14725534437 013064  0                                                                                                    ustar   aipapagi                        aipapagi                                                                                                                                                                                                               #include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid, ppid;

    // Get the PID of the current process
    pid = getpid();

    // Get the PPID of the current process
    ppid = getppid();

    printf("Current Process ID (PID): %d\n", pid);
    printf("Parent Process ID (PPID): %d\n", ppid);

    return 0;
}
                                                                                                                                                                     example3.c                                                                                          0000664 0002422 0002424 00000001203 14725534437 013060  0                                                                                                    ustar   aipapagi                        aipapagi                                                                                                                                                                                                               #include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT
void sigint_handler(int sig) {
    printf("\nCaught signal %d (SIGINT). Exiting gracefully...\n", sig);
    exit(0);
}

int main() {
    // Register the SIGINT handler
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Process ID: %d\n", getpid());
    printf("Press Ctrl+C to trigger SIGINT.\n");

    // Infinite loop to keep the program running
    while (1) {
        printf("Running... Press Ctrl+C to exit.\n");
        sleep(2);
    }

    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                             example4.c                                                                                          0000664 0002422 0002424 00000001236 14725534437 013067  0                                                                                                    ustar   aipapagi                        aipapagi                                                                                                                                                                                                               #include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGINT (does nothing)
void sigint_handler(int sig) {
    printf("\nReceived SIGINT (signal %d), but ignoring it.\n", sig);
}

int main() {
    // Register the SIGINT handler to ignore the signal
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Process ID: %d\n", getpid());
    printf("Press Ctrl+C to attempt to send SIGINT.\n");

    // Infinite loop to keep the program running
    while (1) {
        printf("Running... Try pressing Ctrl+C.\n");
        sleep(2);
    }

    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                  example5.c                                                                                          0000664 0002422 0002424 00000003126 14725534437 013070  0                                                                                                    ustar   aipapagi                        aipapagi                                                                                                                                                                                                               #include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler for SIGUSR1 in child
void sigusr1_handler(int sig) {
    printf("Child received SIGUSR1 (signal %d).\n", sig);
}

int main() {
    pid_t pid;

    // Create a pipe for synchronization (optional)
    // ...

    pid = fork();

    if (pid == -1) { // Error
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Register SIGUSR1 handler
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
            perror("signal");
            exit(EXIT_FAILURE);
        }

        printf("Child process ID: %d. Waiting for SIGUSR1...\n", getpid());

        // Infinite loop to keep child alive
        while (1) {
            pause(); // Wait for signals
        }
    } else { // Parent process
        printf("Parent process ID: %d. Child PID: %d\n", getpid(), pid);

        // Sleep for 3 seconds before sending SIGUSR1
        sleep(3);

        printf("Parent sending SIGUSR1 to child.\n");
        if (kill(pid, SIGUSR1) == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        // Optionally, wait for child to handle the signal
        sleep(1);

        // Terminate the child process
        printf("Parent sending SIGTERM to child.\n");
        if (kill(pid, SIGTERM) == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        // Wait for the child process to terminate
        wait(NULL);
        printf("Child process terminated.\n");
    }

    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                          Makefile                                                                                            0000664 0002422 0002424 00000001064 14725534437 012643  0                                                                                                    ustar   aipapagi                        aipapagi                                                                                                                                                                                                               # Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SOURCES = example1.c example2.c example3.c example4.c example5.c

# Object files
OBJECTS = example1 example2 example3 example4 example5

# Default target
all: $(OBJECTS)

# Targets for each file
example1: example1.c
	$(CC) $(CFLAGS) -o $@ $<

example2: example2.c
	$(CC) $(CFLAGS) -o $@ $<

example3: example3.c
	$(CC) $(CFLAGS) -o $@ $<

example4: example4.c
	$(CC) $(CFLAGS) -o $@ $<

example5: example5.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove compiled files
clean:
	rm -f $(OBJECTS)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            