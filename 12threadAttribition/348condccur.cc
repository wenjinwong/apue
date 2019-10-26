#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mtx;

pthread_cond_t cond;

void *
func(void *arg)
{
	pthread_cond_wait(&cond, &mtx);
	printf("working\n");
	pthread_mutex_unlock(&mtx);
	pthread_exit(NULL);
}
int 
main(void)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);

	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mtx, &attr);
	pthread_t id;
	pthread_attr_t at;
	pthread_attr_init(&at);
	pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);

	pthread_create(&id, &at, func, NULL);
	pthread_create(&id, &at, func, NULL);
	pthread_create(&id, &at, func, NULL);
	pthread_create(&id, &at, func, NULL);
	sleep(10);
}
