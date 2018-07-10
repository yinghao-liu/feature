#include <iostream>
using namespace std;

int main(void)
{
	char *str;
	sprintf(str, "this is a only 5 bytes array\n");
	printf("%s\n", str);


	printf("here would not be printed\n");
	return 0;
}

