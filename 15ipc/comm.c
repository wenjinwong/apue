#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>

void 
func(int n)
{
	printf("receive signal\n");
}

int 
main()
{
	pid_t pid;
	pid = fork();
	sigset_t mask;
	sigfillset(&mask);
	if(pid > 0) {
		printf("wait for child\n");
		signal(SIGHUP, func);
		sigsuspend(&mask);
		int fd;
		fd = open("tmp",O_CREAT, S_IRUSR | S_IWUSR);
		int n;
		char buf[100];
		n = read(fd, buf, 100);
		printf("%s", buf);
	}else if(pid == 0) {
		
		int fd = open("tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		int n;
		n = write(fd, "child", 100);
		printf("%s\n", "writed\n");
		kill(getppid(), SIGHUP);
	}
}
