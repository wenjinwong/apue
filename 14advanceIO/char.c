#include<stdio.h>

int 
main(void)
{
	char c = '0';
	printf("%x\n", c);
	char s[10]="123";
	printf("%s\n", s);
	s[3] ='0';
	s[4] =0;
	printf("%s\n",s);

}
