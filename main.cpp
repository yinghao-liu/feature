#include <stdio.h>
#include <unistd.h>
void none_use(void)
{
	printf("none\n");
}
void waste(int a)
{
	float sum = 1.1;
	if (sum >0) {
		for (int i=0; i<900; i++)
		{
			sum = sum * sum;
		}
	} else {
		printf("less than 0\n");
	}
	int i = 0;
	if (a > 0) {
		i++;
	} else {
		i++;
	}
}

int main(void)
{
	waste(0);
	waste(1);
	waste(2);
	return 0;
}
