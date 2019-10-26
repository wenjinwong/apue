#include<stdlib.h>
#include<pthread.h>

struct foo {
	int				f_count;
	pthread_mutex_t f_lock;
	int				f_id;
	/* ... more stuff here ... */
};

struct foo *
foo_alloc(int id) /* allocate the object */
{
	struct foo *fp;

	if((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		/* continue initialization ... */
	}
	return (fp);
}


void 
foo_hold(struct foo *fp) /* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void
foo_rele(struct foo *fp) /* release a reference to the object */
{
	pthread_mutex_unlock(&fp->f_lock);
	if(--fp->f_count == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void 
cleanup(void *str)
{
	
	printf("%s",(char *)str);
}

void next(void *c)
{
	printf("clean \n");
}

void*
func(void *fp)
{
	foo_hold(fp);
	printf("pid : %ld  ", pthread_self());
	foo_rele(fp);
	char *c = 'c';
//	pthread_cleanup_push(next, (void*)c);
	pthread_exit((void *)0);
}
	
int
main(void)
{
	struct foo fo;
	foo_alloc(&fo);
	pthread_t id[100];
	for(int i = 0; i != 100; i++) {
		pthread_create(&id[i], NULL, func, (void *)&fo);
	}
	return 1;
}

