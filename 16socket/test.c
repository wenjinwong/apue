#include<stdio.h>

int
main(void)
{
	int i = 0x04030201;
	char *cp = (void *)&i;
	printf("%x\n", cp[0]);
}
