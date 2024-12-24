#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2, pid3;
    printf("Here is the parent process, PID: %d\n", getpid());

    pid1 = fork();
    printf("fork1\n");

    if (pid1 < 0) {
        // Error occurred
        exit(EXIT_FAILURE);
    
    } else if (pid1 == 0) {
        // First child process
        printf("First child process, PID: %d\n", getpid());
    } else {
        pid2 = fork();
        printf("fork2\n");
        if (pid2 == 0) {
            // Second child process
            printf("Second child process, PID: %d\n", getpid());
        } else {
            printf("fork3\n");
            pid3 = fork();
            if (pid3 == 0) {
                // Third child process
                printf("Third child process, PID: %d\n", getpid());
            }
            else{
                wait(NULL);
                printf("Parent process waited for children\n");
            }
        }
    }


    return 0;
}