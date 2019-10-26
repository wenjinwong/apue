#include<stdio.h>

void destructor(void *);

pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;
void
thread_init(void) {
	err = pthread_key_create(&key, destructor);
}

int 
threadfunc(void *arg)
{
	pthread_once(&init_done, thread_init);
}

pthread_getsocific(key);

