#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void 
abort(void)
{
	sigset_t mask;
	struct sigaction action;
	/* POSIX-style abort() function */

	/* Caller can't ignorer SIGABRT, if so reset to default */
	sigaction(SIGABRT, NULL, &action);
	if(action.sa_hander = SIG_IGN) {
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}

	if(action.sa_handler == SIG_DFL)
		fflush(NULL);	/* flush all open stdio streams */
	
	/* Caller can's block SIGABRT; mask sure it's unblocked */
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	segprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	/* send the signal; */

	/* if we are done , process caught SIGABRT and returned */
	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}

