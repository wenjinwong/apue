#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#define handle_error_en(en, msg) \
	do { errno =  en; \
		perror(msg); \
		exit(EXIT_FAILURE); } while(0);

static pthread_mutex_t mtx;

static void *
bad_thread(void *ptr)
{
	printf("\n [bad owner] Setting lock...\n");
	pthread_mutex_lock(&mtx);
	printf("[bad owner] locked. now exiting without unlocking.\n");
	pthread_exit(NULL);
}

static void*
second_thread(void *ptr)
{
	int i = 5;
	while(i--)
		{
			int s = pthread_mutex_lock(&mtx);
			if(s == EOWNERDEAD)
			{
				printf(" return EOWNERDEAD\n");
				s = pthread_mutex_consistent(&mtx);
				if( s != 0)
					handle_error_en(s, "pthread_mutex_consistrnt");
				pthread_mutex_unlock(&mtx);
				printf("unlocking\n");
			}
			else{
				printf("normal unlock\n");
				pthread_mutex_unlock(&mtx);
			}
		}
}

int 
main(void)
{
	pthread_t thr;
	pthread_mutexattr_t attr;
	int s;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
	/* set robustnuss */
	pthread_mutex_init(&mtx,&attr);
	pthread_create(&thr, NULL, bad_thread, NULL);
	sleep(1);
	pthread_create(&thr, NULL, second_thread, NULL);
	sleep(12);
}



