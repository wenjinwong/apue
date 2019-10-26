#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int counter = 0;
pthread_mutex_t gmutex;

void *
doit(void *arg)
{
	int i, val;
	for(i = 0; i < 5000; i++) {
		pthread_mutex_lock(&gmutex);
		pthread_mutex_lock(&gmutex);
		val = counter;
		printf("%x: %d]n", pthread_self(), val + 1);
		counter = val + 1;
		pthread_mutex_unlock(&gmutex);
		pthread_mutex_unlock(&gmutex);
	}
}

int 
main(int argc, char *argv[])
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);

	// set recursive attribute
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&gmutex, &attr);

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, doit, NULL);
	pthread_create(&tid1, NULL, doit, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_destroy(&gmutex);
	pthread_mutexattr_destroy(&attr);
	return 0;
}
