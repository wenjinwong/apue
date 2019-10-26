#include"apue.h"
#include<ctype.h>

int 
main(void)
{	
	int		c;
	while((c = getchar()) != EOF) {
		if(isupper(c)) 
			c = tolower(c);
		fprintf(stdout, "child: ", 100);
		
		if(putchar(c) == EOF)
			err_sys("output error");
		if(c == '\n')
			fflush(stdout);
	}
	exit(0);
}
