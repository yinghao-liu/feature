#include <iostream>
#include <string>
using namespace std;
void Throw(void)
{
	throw 1;
}
void aa_throw(void)
{
	Throw();
}
void bb_throw(void) noexcept
{
	Throw();
}
int main(void)
{
	try {
		Throw();
	}catch(...){
		cout<<"catch Throw"<<endl;
	}
	try {
		aa_throw();
	}catch(...){
		cout<<"catch aa_throw"<<endl;
	}
	try {
		bb_throw(); // terminate called after throwing
	}catch(...){
		cout<<"catch bb_throw"<<endl;
	}
	cout<<"end"<<endl;
	return 0;
}

