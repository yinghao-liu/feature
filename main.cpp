#include <string.h>
#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <mqueue.h>
#include <stdarg.h>
#define MAX_MQ_MSG 120
using namespace std;
enum debug_level{
	FATAL = 0,
	ERROR,
	WARN,
	INFO,
	DEBUG
};
int log_level=0;
#define log(level, s, ...)	\
	__log(level, "%s:%u(%s): "s, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
void __log(int level, const char *s, ...)
{
	if (level > log_level){
		return;
	}   
	va_list ap; 
	va_start(ap, s); 
	vprintf(s, ap);
	va_end(ap);
}

int main(void)
{
	int ll=20;
	log_level = DEBUG;
	/*
	 * the second argument must be the const string as below, can't be a char* pointer
	 * there is another way to resolve that, but you should malloc memory.
	 *
	 * */
	log(FATAL, "hello,%d\n",ll);
	return 0;

}
