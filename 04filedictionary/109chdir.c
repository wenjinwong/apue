#include"apue.h"
#include<fcntl.h>
int 
main(void)
{
	if(chdir("/tmp") < 0)
		err_sys("chdir failed");
	printf("chdir to /tmp succeeded\n");
	creat("tmp.c", O_RDWR);
	unlink("foo");
	exit(0);

}
