#include"apue.h"

static void sig_int(int);

int main(void)
{
	sigset_t newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal (SIGINT) error");

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");

	pr_mask("in critic region: ");

	if(sigsuspend(&waitmask)!=-1)
		err_sys("sigsuspend error");

	pr_mask("after return from sigsupend: ");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK ERROR");

	pr_mask("program exit: ");
	exit(0);
}

static void
sig_int(int signo)
{
	pr_mask("\n sig_int: ");
}

