#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<signal.h>

void
sig(int signo)
{
}


int 
main()
{
	signal(SIGALRM, sig);
	alarm(2);
	sleep(10);
}
