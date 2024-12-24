#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


int main() {
    pid_t pid;
    FILE *fp;

    pid = fork();
    if (pid < 0) {
        // Error occurred
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        fp = fopen("pid.txt", "w");
        if (fp == NULL) {
            printf("Error opening file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "%d", getpid());
        fclose(fp);
        printf("Child Process: Finished writing to file\n");
    } else {
        // Parent process
        wait(NULL); // Wait for child process to finish
        printf("Parent process: waited for child\n");
        fp = fopen("pid.txt", "a");
        if (fp == NULL) {
            printf("Error opening file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(fp, "\n%d", getpid());
        fclose(fp);
        printf("Parent Process: Finished writing to file\n");
    }

}

