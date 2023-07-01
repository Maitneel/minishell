#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *out_txt = (2 <= argc ? (argv[1]) : "hogehoge");

    sleep(1);
    printf("slow_write : %s\n", out_txt);
    return 0;
}