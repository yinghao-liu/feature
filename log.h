#ifndef _LOG_H_
#define _LOG_H_
#define log(level, s, ...)  \
	    __log(level, "%s:%u(%s): "s, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

extern int log_level;
enum debug_level{
	FATAL = 0,
	ERROR,
	WARN,
	INFO,
	DEBUG
};
void __log(int level, const char *s, ...);
#endif
