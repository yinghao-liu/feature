#ifndef _NDREQUEST_H_
#define _NDREQUEST_H_
#include <map>
#include <string>
#include <mqueue.h>
#include <stdint.h>
#include <pthread.h>
using std::map;
using std::string;

#pragma pack (1)
struct msg_head{
	uint8_t  sign[4];		// sign，HTTP is the default
	uint16_t len;			// data len (do not contains this head)
	uint8_t  encrypt_type;  // encrypt typ(0:none,1:xor,2:aes)
	uint8_t  keep_alive;	// if keep alive(1:keep alive)
};
#pragma pack ()
struct request_data{
	int fd;
	uint16_t len;
	uint8_t  encrypt_type;
	uint8_t  keep_alive;
	time_t modify;	/*last time of data modify*/
	string data;
};
class response{
public:
	int init(int pth_num=6);
	void add_to_epoll(int accefd);
	~response();
protected:
	int epoll_init(void);
	int pthread_init(int pth_num);
	int mq_init(void);
	static void *write_to_mq(void *arg);
	static void *read_from_mq(void *arg);
	void purge(void);
	int process_connection(int fd);
	int recv_head(request_data &req_head);
	int recv_body(request_data &req_body);
	int response_op(request_data &req_body);

private:
	int ep_fd;			// epoll fd, for waiting reading
	string mq_name;
	mqd_t mq_write;		// can be treated as mq fd, for writing
	mqd_t mq_read;		// for reading
	map<int, request_data> conn;

	int pth_read_num;
	pthread_t *pth_read;
	pthread_t pth_write;
};

#endif
