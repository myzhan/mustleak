#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        // child
        while(1) {
            sleep(10);
        }
    } else {
        printf("Child pid is %d\n", pid);
        while(1) {
            sleep(10);
        }
    }
    return 0;
}