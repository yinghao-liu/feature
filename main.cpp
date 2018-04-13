#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

vector<string> split(char delimit, const string &str)
{
	size_t start=0;
	size_t end=0;
	string sub;
	vector<string> result;
	while (string::npos != (end=str.find(delimit, start))){
		sub = str.substr(start, end-start);
		result.push_back(sub);
		start = end+1;
	}
	/*the last part after the last delimit*/
	sub = str.substr(start);
	result.push_back(sub);
	return result;
}

int main(void)
{
	ifstream fs;
	fs.open("data");
	if (!fs.is_open()){
		cout<<"open file error"<<endl;
		return -1;
	}
	vector<string> split_line;

	string line;
	while (1){
		getline(fs, line);
		if (!fs.good()){
			break;
		}
		split_line = split('\t', line);
		for (auto &i : split_line){
			cout<<i<<endl;
		}
		cout<<"-----------------"<<endl;
	}

	try{
		//here would out_of_range
		cout<<split_line.at(50);
	}catch (out_of_range &err){
		cerr<<err.what()<<endl;
	}
	return 0;
}

