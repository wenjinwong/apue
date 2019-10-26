#include<stdio.h>

void f2(char *buf)
{
	printf("addr: %p   %s\n", buf, buf);
	buf[3] = 0;
}

int f1()
{
	char buf[10] = "123456789";
	buf[9] = 0;
	printf("buf + 20%c", *(buf + 20));
	f2(buf);
	printf("%s  \n", buf);
	return 0;
}

int main()
{
	
	f1();
}
