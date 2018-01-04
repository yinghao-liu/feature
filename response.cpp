#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "log.h"
#include "response.h"

#define PTH_READ_NUM	12
#define MAX_MQ_MSG 		120

/*******发送数据的信息头*******/
#define SIGN	"HTTP"
using namespace std;
int response::init(int pth_num)
{
	ep_fd = -1;
	pth_read_num = pth_num;
	if (-1 == mq_init()){
		return -1;	
	}
	if (-1 == epoll_init()){
		return -1;
	}
	if (-1 == pthread_init(pth_num)){
		return -1;
	}
}
int response::mq_init(void)
{
	struct mq_attr attr;
	memset(&attr, '\0', sizeof (attr));
	attr.mq_maxmsg = MAX_MQ_MSG;
	attr.mq_msgsize = sizeof (request_data);
	
	mq_name = "/";
	mq_name += NAME;
	mq_unlink(mq_name.c_str());
	mq_write = mq_open(mq_name.c_str(), O_RDWR|O_CREAT, S_IRWXU, &attr);
	if(-1 == mq_write){
		log(ERROR, "mq_open: %s\n",strerror(errno));
		return -1;
	}
	mq_read = mq_open(mq_name.c_str(), O_RDWR|O_CREAT, S_IRWXU, &attr);
	if(-1 == mq_read){
		log(ERROR, "mq_open: %s\n",strerror(errno));
		mq_close(mq_write);
		return -1;
	}
}
int response::epoll_init(void)
{
	ep_fd = epoll_create(1);//this argument is not important
	if (-1 == ep_fd){
		log(ERROR, "epoll_creat: %s\n",strerror(errno));
		return -1;
	}
}
int response::pthread_init(int pth_num)
{
	if (-1 == pthread_create(&pth_write, NULL, write_to_mq, (void *)this)){
		log(ERROR, "pthread_create: %s\n",strerror(errno));
		return -1;
	}

	pth_read = (pthread_t *)calloc(pth_read_num, sizeof (pthread_t));
	if (NULL == pth_read){
		log(ERROR, "calloc: %s\n",strerror(errno));
		return -1;
	}
	for(int tick=0; tick<pth_read_num; tick++){
		if (-1 == pthread_create(&pth_read[tick], NULL, read_from_mq, (void *)this)){
			log(ERROR, "pthread_create: %s\n",strerror(errno));
			return -1;
		}
	}
}
response::~response()
{
	if (-1 == ep_fd){
		close(ep_fd);
	}
	if (NULL != pth_read){
		free(pth_read);
	}
	close(mq_write);
	close(mq_read);
	mq_unlink(mq_name.c_str());
}

void *response::read_from_mq(void *arg)
{
	ssize_t msg_recv;
	int ret;
	request_data data;
	response *self=(response *)arg;
	while (1){
		msg_recv = mq_receive(self->mq_read, (char *)&data, sizeof (data), NULL);
		if(-1 == msg_recv){
			log(ERROR, "mq_receive\n");
			continue;
		}
		ret = self->response_op(data);
		if ((-1 == ret) || (0 == data.keep_alive)){
			log(INFO, "del fd %d from epoll and close it\n", data.fd);
			epoll_ctl(self->ep_fd, EPOLL_CTL_DEL, data.fd, NULL);
			close(data.fd);
		}
		self->conn.erase(data.fd);
	}
	return NULL;
}
/*this function run in single thread*/
void *response::write_to_mq(void *arg)
{
#define MAX_WAIT_FD		24
	struct epoll_event ev[MAX_WAIT_FD];
	int fds_num;
	response *self=(response *)arg;
	while (1){
		fds_num=epoll_wait(self->ep_fd, ev, MAX_WAIT_FD, 60*1000);//60 s = 1 minutes
		if(-1 == fds_num){
			log(ERROR, "epoll_wait: %s\n",strerror(errno));
			continue;
		} else if (0 == fds_num){
			log(WARN, "epoll_wait timeout\n");
			self->purge();
			continue;
		}
		for (int tick=0; tick<fds_num; tick++){
			log(INFO, "epoll_wait fd %d, events is %#.4x\n", ev[tick].data.fd, ev[tick].events);
			log(INFO, "EPOLLIN is %#.4x, EPOLLRDHUP is %#.4x, EPOLLERR is %#.4x, EPOLLHUP is %#.4x\n", EPOLLIN, EPOLLRDHUP, EPOLLERR, EPOLLHUP);
			if (EPOLLIN != ev[tick].events){
				log(WARN, "remove fd %d and close it\n", ev[tick].data.fd);
				if (-1 == epoll_ctl(self->ep_fd, EPOLL_CTL_DEL, ev[tick].data.fd, NULL)){
					log(ERROR, "epoll_ctl EPOLL_CTL_DEL :%s\n", strerror(errno));
				}
				close(ev[tick].data.fd);
				continue;
			}
			/*write to mq if the whole request has received*/
			if (-1 == self->process_connection(ev[tick].data.fd)){
				log(ERROR, "process_connection error, and will remove %d\n", ev[tick].data.fd);
				epoll_ctl(self->ep_fd, EPOLL_CTL_DEL, ev[tick].data.fd, NULL);
				close(ev[tick].data.fd);
				self->conn.erase(ev[tick].data.fd);
			}
		}
	}
	return NULL;
}
void response::purge(void)
{
#define PURGE_TIME	(2*60)//5 minutes
	time_t now=time(NULL);
	map<int, request_data>::iterator it;
	for (it=conn.begin(); it!=conn.end(); it++){
		if ((now-it->second.modify) > PURGE_TIME){
			if (0 == it->second.keep_alive){
				log(INFO, "del fd %d from epoll and close it\n", it->first);
				epoll_ctl(ep_fd, EPOLL_CTL_DEL, it->first, NULL);
				close(it->first);
			}
			conn.erase(it);
		}
	}
}

void response::add_to_epoll(int accefd)
{
	struct epoll_event ev;
	memset(&ev, '\0', sizeof (ev));
	ev.events = EPOLLIN|EPOLLRDHUP;
	ev.data.fd=accefd;
	log(INFO, "add accefd to epoll fd is %d\n", accefd);
	if (-1 == epoll_ctl(ep_fd, EPOLL_CTL_ADD, accefd, &ev)){
		log(ERROR, "add accefd to epoll error: %s\n",strerror(errno));
		close(accefd);
	}
}
int response::recv_head(request_data &req_head)
{
	ssize_t  len;
	msg_head head;
	len = recv(req_head.fd, &head, sizeof (head), 0);
	if (len <= 0){
		log(ERROR, "recv: %s\n",len==-1?strerror(errno):"peer has performed an orderly shutdown");
		return -1;
	} else if (sizeof (head) != len){
		log(WARN, "recved head len is not right, it should be %u, while the real is %u\n",\
				sizeof (head), len );
		return -1;
	}
	if (0 != memcmp(head.sign, SIGN, sizeof (head.sign))){
		log(WARN, "the data received is not what I want\n");
		return -1;
	}
	req_head.len = ntohs(head.len);
	req_head.encrypt_type = head.encrypt_type;
	req_head.keep_alive = head.keep_alive;
	req_head.modify = time(NULL);
	return 0;
}
int response::recv_body(request_data &req_body)
{
	char body[128]={0};
	ssize_t  len;

	len = recv(req_body.fd, body, sizeof (body), 0);
	if (len <= 0){
		log(ERROR, "recv: %s\n",len==-1?strerror(errno):"peer has performed an orderly shutdown");
		return -1;
	}
	log(INFO, "recv body: %s, and recv len: %u\n", body, len);
	ssize_t remain_len;
	remain_len = req_body.len - req_body.data.length();
	if (remain_len > 0){
		req_body.data.append(body, (len<remain_len)?len:remain_len);	
		req_body.modify = time(NULL);
	}else{
		log(WARN, "peer send needless data\n");
		return 0;
	}
	log(INFO, "head indicate the len is %u, and the real len now is %u\n", req_body.len, req_body.data.length());
	if (req_body.data.length() >= req_body.len){
		/*here may do the decryption*/
		log(INFO, "will send to mq, requst body data is %s\n", req_body.data.c_str());
		if (-1 == mq_send(mq_write, (char *)&req_body, sizeof (req_body), 0)){
			log(ERROR, "mq_send %s\n", strerror(errno));
			return -1;
		}
	}
	return 0;

}
int response::process_connection(int fd)
{
	map<int, request_data>::iterator it;
	it = conn.find(fd);
	if (it == conn.end()){//new connection
		log(INFO, "this is new connection, fd is %d\n", fd);
		request_data &head=conn[fd];
		head.fd = fd;
		return recv_head(head);
	} else {//old connection
		log(INFO, "this is old connection, map size is %d\n", conn.size());
		return recv_body(conn[fd]);
	}
}
int response::response_op(request_data &req_body)
{
	static int ti=0;
	log(INFO, "process_connect come in %d, pthread id is %#x\n", ti++, pthread_self());
	log(INFO, "connected_fd is  %d, star at %ld\n", req_body.fd, time(NULL));
/***************************parser request data***************************/	
	
/***************************run what should do***************************/	

/***************************before send back***************************/	
	msg_head head;
	memcpy(head.sign, SIGN, sizeof (head.sign));
	head.len = htons(req_body.data.length());
	head.encrypt_type = 0;
	head.keep_alive = req_body.keep_alive;
	/*here may do the encryption*/
/***************************send back***************************/	
	send(req_body.fd, &head, sizeof (head), 0);
	send(req_body.fd, req_body.data.c_str(), req_body.data.length(), 0);

	log(INFO, "connected_fd is  %d, end at %ld\n", req_body.fd, time(NULL));
	return 0;
}

