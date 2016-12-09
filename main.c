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
#include <arpa/inet.h>
int main(void)
{
	unsigned int gateip = 0x010ba8c0;
	unsigned char aa[20]={0};
	unsigned char gateway_mac[20]={0};

	char buff[256]="192.168.11.1	0x1	0x2                    	00:1d:a1:7a:a7:bd	* eth2";
    char gateway[16] = {0};
    int iret = 0; 
    int index = 0;
    char *pos = 0;

if(iret == 0)
    {
        pos = buff + 41;
        while(index < 6 && buff + 58)
        {
            if(pos[0] >= 'A' && pos[0] <= 'Z')
            {
                pos[0] -= 0x37;
            }
            else if(pos[0] >= '0' && pos[0] <= '9')
            {
                pos[0] -= 0x30;
            }
            else
            {
                pos++;
                continue;
            }

            if(pos[1] >= 'A' && pos[1] <= 'Z')
            {
                pos[1] -= 0x37;
            }
            else if(pos[1] >= '0' && pos[1] <= '9')
            {
                pos[1] -= 0x30;
            }

            gateway_mac[index++] = (pos[0]<<4)|(pos[1]&0xf);

            pos += 2;
        }
    }
    printf("gateway_mac %02x:%02x:%02x:%02x:%02x:%02x:\n",gateway_mac[0],gateway_mac[1],gateway_mac[2],gateway_mac[3],gateway_mac[4],gateway_mac[5]);


//	inet_ntop(AF_INET, (void *)&gateip, aa, 16);
	printf("%s\n",aa);
	return 0;
}
