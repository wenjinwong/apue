#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd;
	fd = open("/dev/fd/1",O_RDWR);
	close(1);
	write(fd, "fadsa", 10);
}
	


