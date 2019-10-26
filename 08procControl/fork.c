#include<unistd.h>
#include<stdio.h>
#include<time.h>

int
main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
		exit(0);
	sleep(3);
	printf("ppid = %ld", getppid());
}
