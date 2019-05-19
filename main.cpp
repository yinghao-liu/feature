//#include <iostream>
#include <mcheck.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
//using namespace std;

void mcheck_exit(enum mcheck_status mstatus)
{
	switch (mstatus) {
	case MCHECK_HEAD:
		printf("Memory preceding an allocated block was clobbered\n");
		break;
	case MCHECK_TAIL:
		printf("Memory following an allocated block was clobbered\n");
		break;
	case MCHECK_FREE:
		printf("A block of memory was freed twice.\n");
	}
	void *buff[256] = {NULL};
	char **symbols = NULL;
	int num_of_symb = 0;
	num_of_symb = backtrace(buff, sizeof (buff));
	symbols = backtrace_symbols(buff, num_of_symb);
	for (int i=0; i<num_of_symb; i++) {
		printf("%s\n", symbols[i]);
	}

	printf("%d\n", __LINE__);
}
int main(int argc, char *argv[])
{
	mcheck(mcheck_exit);
	char *p = NULL;
	p = (char *)malloc(100);            /* Never freed--a memory leak */

	free(p);
	free(p);
}


