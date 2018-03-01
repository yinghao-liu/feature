#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct mem{
	mem(){cout<<"mem default, num:"<<num<<endl;}
	mem(int i):num(i){cout<<"mem, num:"<<num<<endl;}
	int num=2;
};

class group{
public:
	group(){cout<<"grout default, val:"<<val<<endl;}
	group(int i):val('G'),a(i){cout<<"grout default, val:"<<val<<endl;}
	void num_of_a(){cout<<"number of a:"<<a.num<<endl;}
	void num_of_b(){cout<<"number of b:"<<b.num<<endl;}
private:
	char val{'g'};
	mem a;
	mem b{19};
};

int main(void)
{
	mem member;
	cout<<"---------------"<<endl;
	group gg;
	cout<<"---"<<endl;
	gg.num_of_a();
	gg.num_of_b();
	cout<<"---------------"<<endl;

	group gg2(7);
	cout<<"---"<<endl;
	gg2.num_of_a();
	gg2.num_of_b();
	cout<<"---------------"<<endl;

	int a[] = {1,2,3,4};	//OK
	int b[] {1,2,3,4};		//OK
	vector<int> c(3);		//OK
	int c1[3] = {1,2,3};		//OK
	//vector<int> c2(3)={1,2,3};//error: expected ‘,’ or ‘;’ before ‘=’ token
	map<int, string> d{{1, "a"}, {2, "b"}};//OK

	for (auto ds: d){
		cout<<ds.first<<"->"<<ds.second<<endl;
	}
	return 0;
}
