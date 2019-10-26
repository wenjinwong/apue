#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void print(char *c);

int main(void)
{
	char c[] = "test";
	printf("test   %p  0 %d ", c, c[4]);
	void *p = calloc(10, 10);
	void *pa[10];
	void *pp  = calloc(4, 10);
	char *pc = (char*)(pp+4);
	printf("%c  ", *(pc));
	//print(c);
	//_exit(10);
}

void print(char c[])
{
	printf("%s   %p", *c, c);
}
