#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    pid_t pid = fork();
    usleep(10000);
    system("leaks fork_test -q");
}