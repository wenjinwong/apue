#include<unistd.h>
#include<signal.h>

static void 
sig_alarm(int signo)
{
	printf("alarm, continue to work\n");

	printf("getpid = %d\n", getpid());
}

unsigned int
sleep1(unsigned int seconds)
{
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
		return(seconds);
	alarm(seconds);
	pause();
	printf("getpid = %d\n", getpid());
	raise(0);
	kill(getpid(), 9);
	return(alarm(0));
}

int 
main(void)
{
	printf("getpid = %d\n", getpid());
	sleep1(2);
	printf("sleep over");
}



