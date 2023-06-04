#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int is_break;

void rsignal(int id)
{
    printf("\b\bsignal is %d\n", id);
    fflush(stdin);
    is_break--;
    return;
}

int main() {
    signal(2, rsignal);
    signal(3, rsignal);
    is_break = 5;
    while (is_break)
    {
    }
    
    return 0;
}