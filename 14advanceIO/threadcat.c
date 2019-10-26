#include<pthread.h>
#include<stdio.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>

void sig(int no)
{
	printf("signal\n");
}


void *
func(void *arg)
{
	sleep(1);
	sigset_t set;
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	//signal(SIGHUP, SIG_IGN);
	printf("signal arise\n");
	kill(getpid(), SIGHUP);
}

int 
main(void)
{
	pthread_t pid;
	signal(SIGHUP, sig);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&pid, &attr, func, NULL);
	sleep(3);
}
	
