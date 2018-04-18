#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <map>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <inttypes.h>


using namespace std;

#pragma pack(1)
struct udp_head{
	uint8_t		type;
	uint16_t	len;
	char		reserve[1];
};
struct udp_data{
	uint8_t		type;
	uint8_t		len;
	char 		data[0];
};
#pragma pack()
#define UDP_PORT	1813
int send_udp(uint16_t port)
{
	int client_sock;
	client_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == client_sock){
		perror("socket");
		return -1;
	}
	struct sockaddr_in local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	if (-1 == inet_pton(AF_INET, "127.0.0.1", &local_addr.sin_addr.s_addr)){
		perror("inet_pton");
	}
	
	char buff[1024];

	udp_head *send_head;
	udp_data *send_data;
	send_head = (udp_head*)buff;
	send_data = (udp_data*)(buff + sizeof (udp_head));
	send_head->type = 4;
	send_head->len  = sizeof (udp_head);
	
	send_data->type = 1;
	strcpy(send_data->data, "12311112222");
	send_data->len = 11+2;
	send_head->len += send_data->len;

	send_head->len = htons(send_head->len);
		
	
	if (-1 == sendto(client_sock, buff, ntohs(send_head->len), 0, (sockaddr *)&local_addr, sizeof (local_addr))){
		perror("sendto");
	}
	return 0;

}

int main(int argc, char **argv)
{

	send_udp(UDP_PORT);
	return 0;
}

