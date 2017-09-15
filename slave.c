/*
 * Copyright (C) 2017 francis_hao <francis_hao@126.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int sock_fd;
	int acce_fd;
	int s;
	size_t data_len;
	char buff[100]={0};
	struct addrinfo hints;
	struct addrinfo *result,*rp;

	result=rp=NULL;
	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_INET;/*only IPv4*/
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	s = getaddrinfo("192.168.183.128", "6532", &hints, &result);
	if (0 != s){
		printf("getaddrinfo:%s\n",gai_strerror(s));
		return -1;
	}
	for (rp=result; rp!=NULL; rp=rp->ai_next){
		
		sock_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == sock_fd){
			perror("socket");
			continue;;
		}
		s = connect(sock_fd, rp->ai_addr, rp->ai_addrlen);
		if(0 != s){
			perror("connect");
			continue;
		}
		data_len = send(sock_fd, "hello", 5, 0);
		if (-1 == data_len){
			perror("send");
			continue;
		}

	}
	data_len = send(sock_fd, " world", 6, 0);
	close(sock_fd);
	freeaddrinfo(result);

	return 0;
}
