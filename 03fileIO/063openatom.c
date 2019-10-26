#include"apue.h"
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(void)
{
	int fd;
	if((fd = open("file", O_WRONLY)) < 0){
		if(errno == ENOENT) {
			if((fd = creat("file", O_CREAT)) < 0)
				err_sys("creat error");
		}else {
			err_sys("open error");
		}
	}
}
