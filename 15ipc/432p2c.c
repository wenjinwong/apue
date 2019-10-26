#include"apue.h"

int 
main(void)
{
	int			n;
	int			fd[2];
	pid_t		pid;
	char		line[MAXLINE];
	if(pipe(fd) < 0)
		err_sys("pipe error");
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0) {
		write(fd[1], "child", 1000);
	}else if(pid == 0) {
		char buf[1000];
		read(fd[0], buf, 1000);
		printf("%s\n", buf);
	}
}

