#include"apue.h"
#include<sys/resource.h>

#define findid(name)  pr_limits(#name, name)

static void pr_limits(char *, int);

int 
main(void)
{
#ifdef RLIMIT_AS
	findid(RLIMIT_AS);
#endif

	findid(RLIMIT_CORE);
	findid(RLIMIT_CPU);
	findid(RLIMIT_DATA);
	findid(RLIMIT_DATA);
	findid(RLIMIT_FSIZE);
#ifdef RLIMIT_MEMLOCK
	findid(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
	findid(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
	findid(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
	findid(RLIMIT_NICE);
#endif

	findid(RLIMIT_NOFILE);

#ifdef RLIMIT_NPROC
	findid(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
	findid(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
	findid(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
	findid(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
	findid(RLIMIT_SIGPENDING);
#endif

	findid(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
	findid(RLIMIT_SWAP);
#endif

#ifdef RLIMIT_VMEM
	findid(RLIMIT_VMEM);
#endif

	exit(0);
}

static void 
pr_limits(char *name, int resource)
{
	struct rlimit		limit;
	unsigned long long  lim;

	if(getrlimit(resource, &limit) < 0)
		err_sys("getrlimit error for %s", name);
	printf("%-40s  ", name);
	if(limit.rlim_cur == RLIM_INFINITY) {
		printf("(infinite)  ");
	}else {
		lim = limit.rlim_cur;
		printf("%20d  ", lim);
	}

	if(limit.rlim_max == RLIM_INFINITY) {
		printf("(infinite)");
	} else {
		lim = limit .rlim_max;
		printf("%20d", lim);
	}
	putchar((int)'\n');
}


