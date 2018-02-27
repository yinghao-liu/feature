#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t t;
	char des[100]={0};
	t = time(NULL);
	strftime(des, sizeof (des),"%F %T", localtime(&t));
	printf("time is %s\n", des);
	return 0;
}
