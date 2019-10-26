#include<unistd.h>
#include<stdio.h>

int 
main(void)
{
	/* parent listen stdin 
	 * chlid listen net node
	 */

	char buf[1024];
	int ret;
	if((ret = fork()) < 0) {
		perror("bad fork");
	} else if(ret == 0) { /* child */
		int fd;
		fd = open("tmp.file", O_RDWR | O_CREAT, O_IXUSR | O_IRUSR | O_IWUSR);
		char ch[1024];
		while(read(fd, ch, 1024)) {
			write(stdin, ch, 1024);
		}
	} else if(ret > 0) {
		read(stdin, buf, 1024);
		write(stdout, buf ,1024);
	}
}

