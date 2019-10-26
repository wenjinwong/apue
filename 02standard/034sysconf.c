#include<unistd.h>
#include<stdio.h>

int 
main(void)
{
	printf("%d  ", sysconf(_PC_PIPE_BUF)); 
}
