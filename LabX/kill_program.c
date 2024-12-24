#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        // Error occurred
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process, PID: %d\n", getpid());
        while(1){
            printf("Child process is running\n");
            sleep(1);
        }
    } else {
        // Parent process
        printf("Parent process, PID: %d\n", getpid());
        sleep(2);
        kill(pid, SIGKILL);
        printf("Parent process killed child process\n");

    }


}