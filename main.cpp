#include <iostream>
#include <string>
#include "client.h"
using namespace std;

template void fun<int>(int); 
int main(void)
{
	fun(1);
	return 0;
}

