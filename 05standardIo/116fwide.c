#include<stdio.h>
#include<wchar.h>
#include"apue.h"

int 
main(int argc, char *argv[])
{
	FILE *fp;
	if((fp = fopen(argv[1], "r+")) == NULL)
		err_sys("fopen error");
	int fd;
	fd = fileno(fp);
	char buf[MAXLINE];
	setbuf(fp, buf);
	setvbuf(fp, buf, _IOLBF, 100);
	write(fd, "12345679", 100);
	fflush(fp);
	//printf("%p  %d", fp, fd);
	fwide(fp, -5);
}
