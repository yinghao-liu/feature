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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int readfd;
	int writefd;
	pid_t child;

	if (0 != mkfifo("fifo",0644)){
		perror("mkfifo");
	}
	child = fork();
	if (0 == child){/*child process*/
		readfd = open("fifo", O_RDONLY);
		if (readfd == -1){
			perror("open for read\n");
		}
		printf("open for read ok, this is child\n");
		exit(0);
	}else if(-1 == child){/*error*/
		perror("fork");
	}
	/*parents process*/
	sleep(3);
	writefd = open("fifo", O_WRONLY);
	printf("open for write ok,this is parent\n");
	return 0;
}










