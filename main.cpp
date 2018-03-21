#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(void)
{
	int a;
	a=1;
	//auto printa1 = [=]{cout<<++a<<endl; };//error: increment of read-only variable ‘a’
	auto printa2 = [&]{cout<<++a<<endl; };
	auto printa3 = [&](){cout<<++a<<endl; };
	//auto printa4 = [&]()->{cout<<++a<<endl; };//error: expected type-specifier before ‘{’ token
	auto printa5 = [&]()-> void{cout<<++a<<endl; };
	cout<<"before lambda "<<a<<endl;;
	printa2();
	cout<<"after lambda "<<a<<endl;;
	printa3();
	printa5();
	//printa5;//there is no effect
	return 0;
}
