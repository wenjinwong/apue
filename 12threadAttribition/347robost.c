#include<pthread.h>


int 
main(void)
{
	pthread_mutexattr_t tag;
	int rob = 100;
	pthread_mutexattr_init(&tag);
	pthread_mutexattr_setrobust(&tag, PTHREAD_MUTEX_ROBUST);
	pthread_mutexattr_setpshared(&tag, PTHREAD_PROCESS_SHARED);
	pthread_mutexattr_getrobust(&tag, &rob);
	pthread_mutex_consistent(&tag);
	printf("robust : %d\n", rob);
	pthread_mutexattr_destroy(&tag);
}
