// cc -I`brew --prefix readline`/include -L`brew --prefix readline`/lib -lreadline eof_test.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main() {
    char *line;
    while (1)
    {
        line = readline("$> ");
        printf("%p, %s ", line, line);
        if (line != NULL)
        {
            printf("len : %zu", strlen(line));
        }
        printf("\n");
        free(line);
    }
    
}