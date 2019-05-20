#include <stdio.h>
int get_bits(int raw_data)
{
	int bits = 0;
	while (0 != raw_data) {
		bits++;
		raw_data &= (raw_data - 1);// here is the key-point
	}
	return bits;
}
int main(void)
{
	printf("%d\n", get_bits(0xfe));
	return 0;
}
