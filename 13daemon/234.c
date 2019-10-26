#include<unistd.h>
#include<stdio.h>

int 
main(void)
{
	printf("group id: %ld\n", getpgid(0));
	pid_t pid;
	setpgid(0, 0);
	//pid = setsid();
	printf("group id: %ld\n", getpgid(0));
	printf("group id: %ld\n", getpgrp());
	printf("pid: %ld\n", getpid());
	printf("getsid: %ld\n", getsid(getpid()));
	//error printf("sid: %d\n", pid);
	printf("group id: %ld\n", getpgid(0));
	printf("tcgetpgrp: %d\n", tcgetpgrp(STDOUT_FILENO));
	tcsetpgrp(STDOUT_FILENO, 4396);
}
