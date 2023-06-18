#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int write_fd = open("./hoge.temp", (O_RDWR | O_CREAT), 0700);
    if (write_fd < 0) {
        return 0;
    }
    int read_fd = open("./hoge.temp", O_RDONLY);
    unlink("./hoge.temp");
    if (write_fd < 0) {
        return 0;
    }
    write(write_fd, "hogehoge temp\n", 14);
    write(write_fd, "fugafuga temp\n", 14);
    write(write_fd, "piyopiyo temp\n", 14);

    char string[20];
    for (size_t i = 0; i < 3; i++)
    {
        read(read_fd, string, 14);
        printf("%s", string);
    }
    char c = 0;
    while (0 <= read(STDIN_FILENO, &c, 1));
}