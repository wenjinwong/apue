#include"apue.h"
#include<pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *
thr_fn(void *arg)
{
	printids("new thread: ");
	pthread_exit(NULL);
	//return ((void *)0);
}

int 
main(void)
{
	int err;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err != 0)
		err_exit(err, "can not create thread");
	printids("main thread: ");
	sleep(1);
	printf("\n%ld\n", ntid);
	exit(0);

}


