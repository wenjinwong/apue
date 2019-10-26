#include<stdio.h>













void seeptr(void *arg)
{
	arg = (char *)arg;
	printf("%s  %p\n", arg, &arg);
}

void changeptr(void *arg)
{
	arg = (char *)arg;
//	arg[2] = '&';
	printf(" c: %s   %p\n", arg, arg);
	arg = 'g';
//	(arg + 1) = 'j';
	arg = "changed it";
	printf("change:  %s  %p\n", arg, arg);
	seeptr(arg);
}
int 
main(void)
{
	char *ptr = "can you see this";
	printf("%p\n", &ptr);
	seeptr(ptr);
	//changeptr(ptr);
	//seeptr(ptr);
}

