#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include <netinet/ip.h>
#define LISTEN_PORT		11111
#define LISTEN_QUEUE	5

/******************listen**************************/
int listen_port(uint16_t port)
{
	int server_sock;
	struct sockaddr_in local_addr;

	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);    
	local_addr.sin_addr.s_addr = INADDR_ANY;

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock) {
		perror("socket");
		return -1;
	}
	if (-1 == bind(server_sock, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		perror("bind");
		return -1;
	}
	if (-1 == listen(server_sock, LISTEN_QUEUE)){
		perror("listen");
		return -1;
	}
	return server_sock;
}

int process_connect(int connected_fd)
{
	unsigned char buff[200]={0};
	unsigned char send_buff[200]={0};
	int len;

	len = recv(connected_fd, buff, sizeof (buff), 0);
	if (-1 == len){
		perror("recv");
		return -1;
	}
	printf("%s\n",buff);
	strcpy(send_buff, buff);

/********************send**************************/
	send(connected_fd, send_buff, strlen(send_buff), 0);
	close(connected_fd);
	return 0;
}

int main(void)
{
	int sockfd;
	int accefd;
	sockfd = listen_port(LISTEN_PORT);
	if (-1 == sockfd){
		printf("socket creat failed,will exit");
		return -1;
	}
	

	while (1){
		accefd = accept(sockfd, NULL, NULL);
		if (-1 == accefd){
			perror("accept");
			sleep(2);
			continue;
		}
		process_connect(accefd);
	}
	return 0;
}
