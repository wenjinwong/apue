#include"apue.h"

int 
main(void)
{
	char *ptr;
	size_t size;
	if(chdir("/home/a/codes") < 0)
		err_sys("chdir failed");
	ptr = path_alloc(&size);
	if(getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");
	printf("cwd = %s\n", ptr);
	int fd;
	fd = open(".", 1);
	fchdir(fd);
	exit(0);
}
