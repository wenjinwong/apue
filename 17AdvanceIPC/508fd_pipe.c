#include"apue.h"
#include<sys/socket.h>

/*
   return a full duplex pipe a unix domain socket with the
   two file descriptors returned in fd[0] fd[1]/
*/

int 
fd_pipe(int fd[2])
{
	return(socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
