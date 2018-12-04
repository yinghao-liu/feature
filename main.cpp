#include <iostream>
#include <string>
using namespace std;
int num_cstr=0;
int num_cpcstr=0;
int num_mvcstr=0;
int num_destr=0;

class A{
public:
	/*construct*/
	A():d(new int(3))
	{
		cout<<"construct: "<<++num_cstr<<endl;
	}
	/*copy construct*/
	A(A &a):d(new int(*a.get_value()))
	{
		cout<<"copy construct: "<<++num_cpcstr<<endl;
	}
	/*move construct*/
	A(A &&a):d(a.get_value())
	{
		a.set_null();
		cout<<"move construct: "<<++num_mvcstr<<endl;
	}
	~A(void)
	{
		delete d;
		cout<<"destruct: "<<++num_destr<<endl;
	}
	void set_null(void)
	{
		d = nullptr;
	}
	int *get_value(void)
	{
		return d;
	}
private:
	int *d;
};
A get_tmpA()
{
	A k;
	cout<<"in get_tmpA address is: "<<k.get_value()<<endl;
	return k;
}


int main(void)
{
	A j = get_tmpA();	
	cout<<"in main address is: "<<j.get_value()<<endl;
	return 0;
}

