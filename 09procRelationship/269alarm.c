#include<unistd.h>

void f(int signo)
{
	printf("signal\n");
}

int 
main(void)
{
	alarm(1);
	signal(SIG_ALARM
