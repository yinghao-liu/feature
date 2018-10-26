#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main(void)
{
	/********more simple way to detect if match**********/
	int n;
	int tmp;
	n=sscanf("2018-09-10", "%d-%d-%d", &tmp, &tmp, &tmp);
	if (3 == n){
		cout<<"match! n is "<<n<<endl;
	}
	/*******using c++11 regex**************/
	if (regex_match("2018-09-10", regex("\\d{4}-\\d{2}-\\d{2}"))){
		cout<<"match"<<endl;
	}
	return 0;
}

