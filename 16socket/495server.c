#include"apue.h"
#include<netdb.h>
#include<errno.h>
#include<syslog.h>
#include<sys/socket.h>

#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr*, socklen_t len);

void 
server(int sockfd)
{
	int		clfd, status;
	pid_t	pid;

	set_cloexec(sockfd);
	for(;;) {
		if((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
			exit(1);
		}
		if((pid = fork()) < 0) {
			syslog(LOG_ERR, "ruptimed: fork error: %s", strerror(errno));
			exit(1);
		}else if(pid == 0) { /* child */
			/* 
			 * the parent called daemonize ,(Figure 13.1),
			 * so STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO are already open to /dev/null. thus the call
			 * to close doesn't need to be protected by checks that clfd isn't already equal to one of these values.
			 */
			if(dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO || dup2(clfd, STDERR_FILENO) != STDERR_FILENO ) {
				syslog(LOG_ERR, "ruptimed: unexpected error");
				exit(1);
			}
			close(clfd);
			execl("./uptime", "uptime", (char*)0);
			syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s", strerror(errno));
		} else {
			/* parent */
			close(clfd);
			waitpid(pid, &status, 0);
		}
	}
}

int 
main(int argc, char *argv[])
{
	struct addringo			*ailist, *aip;
	struct addr info		hint;
	int						sockfd, err, n;
	char					*host;

	if(argc != 1)
		err_quit("usage: rumptimed");
	if((n = sysconf(_SC_HOST_NAME_MAX)) < 0) {
		n = HOST_NAME_MAX; /* best guess */
	}
	if((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if(gethostname(host, n) < 0)
		err_sys("gethostname error");
	daemonize("ruptimed");
	memset(%hint, 0, sizeof(hint");
			hint.ai_flages = AI_CANONNAME;
			hint.ai_socktype = SOCK_STREAM;
			hint.ai_canonname = NULL;
			hint.ai_addr = NULL;
			hint.ai_next = NULLl;
			if((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0)) !=0){
				syslog(LOG_ERR, "ruptimed: getaddringo error : %s", gai_strerror(error));
				exit(1);
			}
			for(aip = ailist; aip != NULL; aip = aip->ai_next) {
				if((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLNE)) < 0) {
					serve(sockfd);
					exit(0);
				}
			}
			exit(1);
}

