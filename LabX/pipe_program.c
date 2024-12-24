#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(){
    int pipefd[2];
    pid_t pid;
    
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);

    } else if (pid == 0) { // Child process
        printf("Child process\n");
        close(pipefd[1]); // Close the write end of the pipe

        char signal;
        printf("Child process waiting for signal...\n");
        read(pipefd[0], &signal, 1); // Read from the pipe
        if (signal == 'k') {
            printf("Child process received signal\n");
        }

        close(pipefd[1]); // Close the write end of the pipe

    } else { // Parent process
        printf("Parent process\n");
        close(pipefd[0]); // Close the read end of the pipe
        sleep(5);

        char signal = 'k';
        write(pipefd[1], &signal, 1); // Write to the pipe
        printf("Parent process sent signal\n");
        close(pipefd[0]); // Close the read end of the pipe

        wait(NULL);
        
    }


    return 0;
}