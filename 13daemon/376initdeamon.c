#include"apue.h"
#include<syslog.h>
#include<fcntl.h>
#include<sys/resource.h>
void
daemonize(const char *cmd)
{
	int				   i, fd0, fd1, fd2;
	pid_t			   pid;
	struct rlimit	   rl;
	struct sigaction   sa;

	/*
	 * clear file creation mask.
	 */

	/*
	 * get maxinum number of file descriptors.
	 */

	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can not get file limit", cmd);

	/*
	 * become a session leader to lose controlling TTY.
	 */

	if((pid == fork()) < 0)
		err_quit("%s: can not fork", cmd);
	else if(pid != 0) /* parent */
		exit(0);
	setsid();

	/*
	 * ensure future opens won not allocate controlling ttys.
	 */

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can not ignore SIGHUP", cmd);
	if((pid == fork()) < 0)
		err_quit("%s : can not fork", cmd);
	else if(pid != 0) /* parent */
		exit(0);

	/*
	 * change the current working directory to the root so
	 * we won't prevent file systems from being unmounted.
	 */

	if(chdir("/") < 0)
		err_quit("%s: can not change dir tp /", cmd);

	/*
	 * close all open files descriptors.
	 */

	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for(i = 0; i < rl.rlim_max; i++)
		close(i);

	/*
	 * attach file descriptors 0, 1, and 2 to /dev/null.
	 */

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/*
	 * initialize the log file.
	 */

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}

int 
main(void)
{
	daemonize("daemon");
}
