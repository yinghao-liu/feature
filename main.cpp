#include <iostream>
#include <mcheck.h>
using namespace std;


int main(void)
{
	setenv("MALLOC_TRACE", "mtrace_output.log", 1);
	mtrace();

	char *p = NULL;
	p = (char *)malloc(100);            /* Never freed--a memory leak */

	exit(EXIT_SUCCESS);
}

