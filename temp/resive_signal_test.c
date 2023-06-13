#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void rescive_signal(int sig_id) {
    printf("signal : %d\n", sig_id);
}

int main() {
    for (size_t i = 0; i < 256; i++)
    {
        signal(i, rescive_signal);
    }
    signal(SIGINT, rescive_signal);
    signal(SIGQUIT, rescive_signal);

    for (size_t i = 0; i < 5; i++)
    {
        pause();
    }
    
}