#include<stdio.h>
#include<pthread.h>

#define null NULL
void func(void*)
{
	printf("ld\n", pthread_self());
}

int
main(void)
{
	pthread_t pid;
	pthread_create(pid, null, func, null);
}
