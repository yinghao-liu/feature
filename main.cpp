#include <iostream>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main(void)
{
	ssize_t total;
	int out_fd;
	int in_fd;
	in_fd = open("abc.jpg", O_RDONLY);
	out_fd  = open("jj.jpg", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	// Not specified in POSIX.1-2001, nor in other standards.
	// sendfile() will transfer at most 0x7ffff000 (2G) bytes, returning the  number  of  bytes  actually  transferred.
	// (This is true on both 32-bit and 64-bit systems.)
	total = sendfile(out_fd, in_fd, NULL, 0x7ffff000);
	if (-1 == total){
		perror("sendfile");
	}
	cout<<"sendfile byte is "<<total<<endl;
	close(out_fd);
	close(in_fd);

	return 0;
}

