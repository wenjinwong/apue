#include<sys/uio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int 
main(void)
{
	struct iovec vec[10];
	char buf1[1024] = "1234567890";
	vec[0].iov_base = buf1;
	vec[0].iov_len = 1023;
	/* others need to be initiliazed */
	writev(STDOUT_FILENO, vec, 10);
}
