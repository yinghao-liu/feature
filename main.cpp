#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
#pragma pack(1)
struct udp_head{
	uint8_t 	type;
	uint16_t	len;
	char		reserve[1];
};
struct udp_value{
	uint8_t	type;
	uint8_t len;
	char 	data[0];
};
#pragma pack()
#define UDP_PORT	1813
int listen_udp(uint16_t port)
{
	int server_sock;
	server_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == server_sock){
		perror("socket");
		return -1;
	}
	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = INADDR_ANY;

	if (-1 == bind(server_sock, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		perror("bind");
		close(server_sock);
		return -1;
	}
	return server_sock;
}


int main(void)
{

	int sockfd;
	sockfd = listen_udp(UDP_PORT);
	if (-1 ==sockfd){
		return -1;
	}
	char buff[1024];
	udp_head *head = (udp_head *)buff;
	string data;
	ssize_t recv_len;
	struct sockaddr_in 	peer_sock;
	socklen_t peer_sock_len;
	while(1){
		peer_sock_len = sizeof (peer_sock);
		//If a message is too long to fit in buff, excess bytes will be discarded
		recv_len = recvfrom(sockfd, buff, sizeof (buff), 0, (sockaddr *)&peer_sock, &peer_sock_len);
		if (recv_len < 0){
			perror("recvfrom");
		}
		head->len = ntohs(head->len);	
		if (4 == head->type){
			//udp_decode(buff + sizeof (radius_head), head->len - sizeof (radius_head), ntohl(peer_sock.sin_addr.s_addr));		
		}
	}
	return 0;
}

