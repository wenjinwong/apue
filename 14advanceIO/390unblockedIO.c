#include"apue.h"
#include<errno.h>
#include<fcntl.h>

char	buf[500000];

int 
main(void)
{
	int		ntowrite, nwrite;
	char	*ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

	int val;
	val = fcntl(STDOUT_FILENO, F_GETFL, 0);
	val |= O_NONBLOCK;
	fcntl(STDOUT_FILENO, F_SETFL, val);

	ptr = buf;
	while(ntowrite > 0) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if(nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}


	val |= ~O_NONBLOCK;
	fcntl(STDOUT_FILENO, F_SETFL, val);
	exit(0);
}

