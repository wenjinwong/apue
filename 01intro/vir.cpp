#include<iostream>

class base1{
	public:
		virtual void f() { std::cout << " base1" ;}
};

class base2{
	public:
		virtual void f() {std::cout << "base2";}
};

class derived : public base1, public base2{
	int val;
};

int main()
{
	std::cout << sizeof(base1) << "   " << sizeof(base2) << "   " << sizeof(derived);
}
