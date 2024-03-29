#include"apue.h"
#include<pthread.h>

void 
cleanup(void *arg)
{
	printf("cleanup: %s\n", (char *)arg);
	sleep(0.5);
}

void thr_fn1(void *arg)
{
	printf("thread 1 start \n");
	pthread_cleanup_push(cleanup, "thread 1 first handler\n");
	pthread_cleanup_push(cleanup, "thread 1 second handler\n");
	printf("thread 1 push complete \n");
	//if(arg)
	//	return ((void *)1);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(0);
	sleep(1);
	//return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler\n");
	pthread_cleanup_push(cleanup, "thread 2 second handler\n");
	printf("thread 2 push complete\n");
	if(arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int 
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	void		*tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);

	err = pthread_join(tid1, &tret);
	printf("thread 2 exit code %ld\n", (long)tret);
	exit(0);
}
