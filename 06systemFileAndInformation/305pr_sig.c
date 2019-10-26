#include<stdio.h>
#include<string.h>
#include<signal.h>

int
main(void)
{
	psignal(3, "hahaha\n");
	printf("%s", strsignal(3));
}
