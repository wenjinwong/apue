#include"apue.h"
#include<ctype.h>
#include<sys/wait.h>

int 
main(void)
{
	char line[MAXLINE];

	FILE *fpin;

	if((fpin = popen("./func", "r") )== NULL)
		err_sys("popen error");
	for(;;) {
		fputs("prompt>", stdout);
		fflush(stdout);
		if(fgets(line, MAXLINE, stdin) == NULL) /* read from pipe */
			break;
		printf("parent: \n");
		if(fputs(line, stdout) ==EOF)
			err_sys("fputs error to pipe");
	}
	if(pclose(fpin) == -1)
		err_sys("pclose error ");
	putchar('\n');
	exit(0);
} 
