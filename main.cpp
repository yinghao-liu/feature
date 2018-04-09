#include <memory>
#include <iostream>
#include <string>
using namespace std;
//here need a " "(blank space) between "macro" and s in c++11
#define jj(s) joint("macro" s)

void joint(const char *ss)
{
	cout<<ss<<endl;
}

int main(void)
{
	jj("hello");
	return 0;
}

