#include"apue.h"

int main(void)
{
	open("file", 0L, 2);
	if(lseek(STDIN_FILENO, 100, SEEK_CUR) == -1)
		printf("can not seek\n");
	else
		printf("seek ok\n");
	exit(0);

}
