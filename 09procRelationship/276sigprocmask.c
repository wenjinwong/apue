#include "apue.h"
#include <errno.h>

void 
pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	sigprocmask(0, NULL, &sigset);
	if(0){
		err_ret("sigprocmask error");
	} else {
		printf("%s", str);
		if(sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");

		printf("\n");
	}
	errno = errno_save;
}
/*
int 
main(void)
{
	char *str = "str";
	pr_mask(str);
}*/
