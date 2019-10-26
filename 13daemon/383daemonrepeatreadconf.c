#include"apue.h"
#include<pthread.h>
#include<syslog.h>

sigset_t mask;

extern int alreay_running(void);

void 
reread(void arg)
{
	/*  */
}

void
thr_fn(void *arg)
{
	int err, signo;
	for(;;) {
		err = sigwait(&mask, &signo);
		if(err != 0) {
			syslog(LOG_ERR, "sigwait faild");
			exit(1);
		}
		switch(signo) {
			case SIGHUP:
				syslog(LOG_INFO, "re-reading configuration file");
				reread();
				break;
			case SIGTERM:
				syslog(LOG_INFO, "got SIGTERM; exiting");
				exit(0);
			default:
				syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}
	return(0);
}

int
main(int argc, char *argv[])
{
	int				err;
	pthread_t		tid;
	char			*cmd;
	struct sigaction sa;
	if((cmd == strchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;

	/*
	 * become a daemon.
	 */

	daemonize(cmd);

	/*
	 * make sure only one copy of the deamon is running.
	 */

	if(already_running()) {
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	/*
	 * restore SIGHUP default and block all signals .
	 */

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't restore SIGHUP default");
	sigfillset(&mask);
	if((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		err_exit(err, "SIG_BLOCK error");

	/*
	 * create a therad to handle SIGHUP and SITERM
	 */
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if(err != 0)
		err_exit(err, "can not create thread");

	/* 
	 * process with the rest of the daemo.
	 */
	/* ... */
	exit(0);
}
