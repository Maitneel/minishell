// cc -I`brew --prefix readline`/include -L`brew --prefix readline`/lib -lreadline signal.c

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/fcntl.h>

#include <readline/readline.h>

int resived_signal;

void catch_signal(int sig_id) {
    // printf("signal is %d\n", sig_id);
    resived_signal = sig_id;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
    rl_replace_line("", 0);
}

int main () {
    signal(SIGINT, catch_signal);
    signal(SIGQUIT, catch_signal);

    
    char *line;
    while (1)
    {
        resived_signal = 0;
        line = readline("$> ");
        if (line == NULL)
        {
            break;
        }
    }
    
}