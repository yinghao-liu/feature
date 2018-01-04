#include <stdio.h>
#include <stdarg.h>
#include "log.h"

int log_level=FATAL;
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
