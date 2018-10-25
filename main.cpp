#include <iostream>
#include <sys/vfs.h>
#include <sys/statvfs.h> // for sdst.f_flags ST_RDONLY...
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main(void)
{
	struct statfs sdst;
	if (0 != statfs("/dev", &sdst)){
		perror("statfs error");
		return -1;
	}

	struct stat fst;
	if (0 != stat("./LICENSE", &fst)){
		perror("stat error");
		return -1;
	}

	return 0;
}

