#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int 
main(void) 
{
	void *ptr;
	int fd = creat("tmp", S_IRUSR | S_IWUSR);
	ptr = mmap(0, 1024, PROT_WRITE | PROT_READ, MAP_SHARED, fd,  0);
}
