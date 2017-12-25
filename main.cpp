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
#define NAME "test_for_mq"
#define MAX_MQ_MSG 120
using namespace std;
int main(void)
{
	struct mq_attr attr;
	memset(&attr, '\0', sizeof (attr));
	attr.mq_maxmsg = MAX_MQ_MSG;
	attr.mq_msgsize = sizeof (int);

	string queue_name("/");	
	queue_name += NAME;//find it in "/dev/mqueue/"

	mqd_t mq_write;
	mqd_t mq_read;
	mq_write = mq_open(queue_name.c_str(), O_RDWR|O_CREAT, S_IRWXU, &attr);
	if(-1 == mq_write){
		perror("mq_open");
		return -1;
	}
	mq_read = mq_open(queue_name.c_str(), O_RDWR|O_CREAT, S_IRWXU, &attr);
	if(-1 == mq_read){
		perror("mq_open");
		mq_close(mq_write);
		return -1;
	}
	
	int ret;
	for (int fd=0; fd<25; fd++){
		ret=mq_send(mq_write, (char *)&fd, sizeof (fd), 0);
		if (-1 == ret){
			perror("mq_send");
		}
	}
	ssize_t msg_recv;
	int mq_msg;
	for (int fd=0; fd<26; fd++){
		msg_recv = mq_receive(mq_read, (char *)&mq_msg, sizeof (mq_msg), NULL);
		if(-1 != msg_recv){
			printf("message queue received data is %d\n", mq_msg);
		}
		if (fd == 20){
			int fdd = 100;
			mq_send(mq_write, (char *)&fdd, sizeof (fdd), 1);
		}
	}
	mq_close(mq_write);
	mq_close(mq_read);
	mq_unlink(queue_name.c_str());

	return 0;

}
