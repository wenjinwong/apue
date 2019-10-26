#include<iostream>

int 
main(void)
{
	char buf[10]= "aaa";
	char *p = "pppp";
	std::cout << (typeid(buf) == typeid(p));
}
