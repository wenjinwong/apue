#include"apue.h"
#include<errno.h>
#include<fcntl.h>
#define BUFFSIZE 1024
int 
main(void)
{	
again:
	
	printf("again\n");
	int fd;
	char buf[BUFFSIZE];
	fd = open("tmp", O_RDWR, O_APPEND);
	int n;
	if((n = read(fd, buf, BUFFSIZE)) < 0) {
		if(errno = EINTR)
			goto again;
	}
}
