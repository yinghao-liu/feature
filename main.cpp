#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
using namespace std;
/**
what's a pity, there is not a effective C++-idiomatically way to show the reason why a file failed to open
refer to https://stackoverflow.com/questions/17337602/how-to-get-error-message-when-ifstream-open-fails
*/

int main(void)
{
	ifstream fs;
	//ios_base::iostate exceptionMask = fs.exceptions() | std::ios::failbit;
	fs.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		fs.open("data");
	}catch(ios_base::failure& e){
		cout<<strerror(errno)<<endl;
		std::cerr << e.code() << '\n';
		std::cerr << e.code().message() << '\n';
		std::cerr << e.what() << '\n';
	}
	return 0;
}

