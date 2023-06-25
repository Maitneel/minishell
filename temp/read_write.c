#include <fcntl.h>

int main()
{
	int fd;
	char *buf;
	
	buf = malloc(sizeof(char) * 4);
	fd = open("hoge.txt", (O_RDWR));
	read(fd, &buf, 4);
	write(fd, "hoge", 4);
	printf("%s\n", buf);
	// write(fd);
}
