#include<stdio.h>

int 
main(void)
{
	ssize_t size = pathconf(PIPE_BUF);
	printf("%ld\n", size);
}
