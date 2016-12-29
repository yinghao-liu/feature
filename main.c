/*
 * Copyright (C) 2016 francis_hao <francis_hao@126.com>
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	struct in_addr aa;
	unsigned char ss[16]="192.168.0.1";
	ss[11]=ss[12]=ss[13]=ss[14]=ss[15]='\0';

	aa.s_addr=ntohl(0xc0a80001);
	if (0 == memcmp(ss,inet_ntoa(aa),16)){
		printf("%s\n",inet_ntoa(aa));
	}
	return 0;
}
