#include<stdio.h>
#include<unistd.h>

int 
main(void)
{
	char buf[4];
	fgets(buf, 100, stdin);
	fputs(buf, stdout);
}
