#include <iostream>
using namespace std;

int main(void)
{
	const char *ss="wlan0     IEEE 802.11bgn  ESSID:\"123456\"";
	char buff[200]={0};
	sscanf(ss, "%*[^\"]\"%[^\"]", buff);
	printf("%s\n",buff);
	return 0;
}

