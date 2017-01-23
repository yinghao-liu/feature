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
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
void signal_handle(int no)
{
	pid_t pid;
	pid = getpid();	
	printf("pid %u receive signal %u\n",pid,no);
}

int main(int argc,char **argv)
{
	char tick;
	pid_t pdd;
	char *mm;
	mm = (char *)mmap(NULL,sizeof (char),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	*mm=1;
	printf("memory is %u\n",*mm);
	//signal(SIGINT,signal_handle);
	signal(SIGTERM,signal_handle);
	for (tick=0;tick<5;tick++){
		pdd = fork();
		if (-1 == pdd ){
			perror("fork");
		}else if (0 == pdd){	//child process
			printf("child #%u started pid is %u\n",tick,getpid());
			*mm=tick;
			printf("child #%u pid is %u  memory is %u\n",tick,getpid(),*mm);
			while (1);
		}else{	//father
			continue;	
		}
	}
	printf("child #%u pid is %u  memory is %u\n",tick,getpid(),*mm);
	while (1);
	return 0;
}
