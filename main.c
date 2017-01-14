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
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/shm.h>
#include "common.h"

int main(int argc,char **argv)
{
	int shmid;
	key_t ipckey;
	//char *shmaddr = NULL;
	shm_data *shmaddr = NULL;	//struct pointer
	int shm_size = sizeof (shm_data);
	ipckey = SYS_IPCSHM_KEY;
	shmid = shmget(ipckey, shm_size, IPC_CREAT | 0666);

	if(shmid == -1)
    {
        perror("creat shm error");
        return -1;
    }

    shmaddr = (shm_data *)shmat(shmid,0,0);
    if(shmaddr == (shm_data *)(~0))
    {
        perror("attach shm error!");
        return -1;
    }
	memset(shmaddr, 0x0, shm_size);
	shmaddr->parray = &shmaddr->array[0];
	shmaddr->array[0]=0;
	shmaddr->array[1]=1;
	shmaddr->array[2]=2;
	shmaddr->array[3]=3;
	shmaddr->array[4]=4;
	shmaddr->array[5]=5;
	shmaddr->array[6]=6;
	shmaddr->array[7]=7;
	printf("main shmaddr->parray point to 0 is %p\n",shmaddr->parray);
	printf("main index %u addr is %p\n",shmaddr->array[0],&shmaddr->array[0]);
	printf("main index %u addr is %p\n",shmaddr->array[1],&shmaddr->array[1]);
	printf("main index %u addr is %p\n",shmaddr->array[2],&shmaddr->array[2]);
	printf("main index %u addr is %p\n",shmaddr->array[3],&shmaddr->array[3]);
	printf("main index %u addr is %p\n",shmaddr->array[4],&shmaddr->array[4]);
	printf("main index %u addr is %p\n",shmaddr->array[5],&shmaddr->array[5]);
	printf("main index %u addr is %p\n",shmaddr->array[6],&shmaddr->array[6]);
	printf("main index %u addr is %p\n",shmaddr->array[7],&shmaddr->array[7]);
	shmdt(shmaddr);
	sleep(8);
	//shmctl(shmid,IPC_RMID,0);
	exit(0);
	return 0;
}
