#include <memory>
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	unique_ptr<int> up1(new int(11));
	//unique_ptr<int> up2 = up1;//up1 can not be copied
	cout<<*up1<<endl;

	unique_ptr<int> up3 = move(up1);
	cout<<*up3<<endl;
	//cout<<*up1<<endl;//result in Segmentation fault (core dumped)
	up3.reset();
	up3.reset();//all is ok


	shared_ptr<int> sp1(new int(22));
	auto sp2 = sp1;
	cout<<*sp1<<endl;
	cout<<*sp2<<endl;
	sp1.reset();
	//cout<<*sp1<<endl;//result in Segmentation fault (core dumped)
	cout<<*sp2<<endl;
	sp2.reset();
	
	shared_ptr<int> sp33(new int(33));
	auto sp44=sp33;
	weak_ptr<int> wp=sp33;
	cout<<wp.use_count()<<endl;
	sp33.reset();	
	cout<<wp.use_count()<<endl;
	sp44.reset();	
	cout<<wp.use_count()<<endl;

	return 0;
}

