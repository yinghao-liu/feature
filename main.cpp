#include <stdio.h>
extern char **environ;
int main(void)
{
	char **env;
	for (env=environ; *env!=NULL; env++){
		printf("%s\n", *env);
	}
	return 0;
}
