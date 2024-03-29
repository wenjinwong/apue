#include<unistd.h>
#include<fcntl.h>
#include<fcntl.h>

int 
main(int argc, char *argv[])
{
	int i, wfd, rfd, n;
	char buf;
	if(argc != 3)
	{
		printf("Usage: cp file1 file2 \2");
		exit(1);
	}
	if((rfd = open(argv[1], O_RDONLY)) < 0)
		err_sys("open file1");
	if((wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, FILE_MODE)) < 0)
		err_sys("open file2");
	while(read(rfd, &buf, 1))
	{
		if(buf == '\0')
			continue;
		if(write(wfd, &buf, 1) < 0)
			err_sys("write");
	}

	if(n < 0)
		err_sys("read");
}
 
