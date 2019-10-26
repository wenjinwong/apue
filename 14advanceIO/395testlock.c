#include"apue.h"
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

pid_t 
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type;		/* f_rdlck, or f_wrlck */
	lock.l_start = offset;	/* byte offset, relatice to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */
	if(fcntl(fd, F_GETLK, &lock) < 0)
		err_sys("fcntl error");
	if(lock.l_type == F_UNLCK)
		return(0);			/* false, region isn't locked by another proc */
	return(lock.l_pid);		/* true, return pid of lock owner */

}


#define if_read_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

int 
main(void)
{
	int fd;
	fd = open("000", O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);
	perror("open");	
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_END;
	lock.l_start = 0;
	lock.l_len = 0;
	fcntl(fd, F_SETLK, lock); 
	read_lock(fd, 0, SEEK_SET, 0);
	int ret = lock_test(fd, F_RDLCK, 0, SEEK_SET, 0);
	printf("%d\n", lock.l_pid);
	if(ret == 0) 
		fprintf(stderr, "unlock\n", 100);
	else
		printf("%d\n", ret);
}
