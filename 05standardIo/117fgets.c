#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int 
main(void)
{
	printf("%d  ", BUFSIZ);
	char buf[100];
	fgets(buf, 100, stdin);
	fputs( buf, stdout);
}
