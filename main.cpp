#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <unistd.h>
using namespace std;

void print1(void)
{
	for (int i=0; i<1000; i++){
		printf("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n");
		usleep(1);
	}
}
void print2(void)
{
	for (int i=0; i<1000; i++){
		printf("222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222\n");
		usleep(3);
	}
}
int main(void)
{
	thread a(print1);
	thread b(print2);
	
	a.join();
	b.join();
	cout<<"completed"<<endl;
	return 0;
}
