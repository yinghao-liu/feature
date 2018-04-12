#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define port 7777
int main(void)
{
	int server_sock1;
	int server_sock2;
	struct sockaddr_in local_addr;

	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);    
	local_addr.sin_addr.s_addr = INADDR_ANY;

	server_sock1 = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock1) {
		perror("socket1");
		return -1;
	}
	server_sock2 = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock2) {
		perror("socket2");
		return -1;
	}

	int aa=1;
	if(-1 == setsockopt(server_sock1, SOL_SOCKET, SO_REUSEADDR, &aa, sizeof (aa))){
	//if(-1 == setsockopt(server_sock1, SOL_SOCKET, SO_REUSEPORT, &aa, sizeof (aa))){
		perror("setsockopt\n");
	}
	if(-1 == setsockopt(server_sock2, SOL_SOCKET, SO_REUSEADDR, &aa, sizeof (aa))){
	//if(-1 == setsockopt(server_sock2, SOL_SOCKET, SO_REUSEPORT, &aa, sizeof (aa))){
		perror("setsockopt\n");
	}

	if (-1 == bind(server_sock1, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		perror("bind1");
		close(server_sock1);
		return -1;
	}
	//listen(server_sock1, 10);
	printf("bind and listen sock1 is over\n");
	if (-1 == bind(server_sock2, (struct sockaddr*)&local_addr, sizeof (local_addr))){
		perror("bind2");
		close(server_sock2);
		return -1;
	}
	printf("bind sock2 is over\n");
	return 0;
}

