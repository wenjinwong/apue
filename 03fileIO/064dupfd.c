#include<unistd.h>

int main()
{
	int new_fd;
	new_fd = dup(1);
	char buf[10] = "asd;fas";
	write(new_fd, buf, 10);
	new_fd = dup2(1, 3);
	write(new_fd, buf, 10);
}
