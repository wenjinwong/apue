#include<netdb.h>
#include<stdio.h>

int
main(void)
{
	struct hostent *t;
	t = gethostent();
	printf("%s\n", t->h_name);
	printf("%d\n", t->h_addrtype);
}
