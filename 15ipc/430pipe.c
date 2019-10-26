#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>


int 
main(void)
{
	int fd[2];
	if(pipe(fd) == -1)
		perror("pipe(fd)");
	//if((fstat(fd[0])) == 1)
	//	printf("is pipe\n");
	pid_t pid;
	
	if((pid = fork()) < 0)
		printf("fork errror\n");
	else if(pid > 0) {
		/* parent */
		close(fd[0]);
		write(fd[1], "hello child\n", 100);
	} else {
		/* child */
		close(fd[1]);
		char buf[100];
		read(fd[0], buf, 100);
		printf("receive: %s\n", buf);
	}
}

