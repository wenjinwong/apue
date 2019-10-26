#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *
func(void *arg)
{
	int ret;
	ret = pthread_mutex_lock(&mutex);
	printf("abort() %d\n", ret);
	pthread_exit(0);
	pthread_mutex_unlock(&mutex);
}

int 
main(void)
{
	int ret;
	pthread_t pid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
	ret = pthread_create(&pid, &attr, func, (void *)1);
	printf("ret: %d\n", ret);
	sleep(1);
	ret = pthread_create(&pid, &attr, func, (void *)1);
	sleep(1);
	printf("ret: %d\n", ret);
	ret = pthread_create(&pid, &attr, func, (void *)1);
	sleep(1);
	printf("ret: %d\n", ret);
	sleep(10);
	//pthread_join(pid, NULL);
}
