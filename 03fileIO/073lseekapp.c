#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd = open("file", 2, O_APPEND);
	lseek(fd, 100, 2);
	char buf[100] = "hello";
	write(fd, buf, 100);
}
