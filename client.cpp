#include <iostream>
#include <string>
#include "client.h"
using namespace std;

template void fun<int>(int); 
void funfun(int a)
{
	fun(a);
}

