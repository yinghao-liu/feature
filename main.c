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
char *tmp(void)
{
	char a=0x55;
	printf("now in function tmp a is %u, and addr is %p\n",a,&a);
	return &a;
}
int main(void)
{

	char size_1[200]={0};
	char size_2[300]={0};
	//char *pa=NULL;
	//pa=tmp();
	//printf("now in function mai a is %u, and addr is %p\n",*pa,pa);
	printf("size_1 addr is %p,end size_1 is %p\n",size_1,&size_1[199]);
	printf("size_2 addr is %p,end size_2 is %p\n",size_2,size_2+300-1);
	printf("-----------\n");
	printf("size_2[400] data is %u, and addr is %p\n",size_2[400],&size_2[400]);
	printf("size_1[96] data is %u, and addr is %p\n",size_1[96],&size_1[96]);
	size_1[96]=12;
	printf("size_2[400] data is %u, and addr is %p\n",size_2[400],&size_2[400]);
	printf("size_1[96] data is %u, and addr is %p\n",size_1[96],&size_1[96]);
	size_2[400]=25;
	printf("size_2[400] data is %u, and addr is %p\n",size_2[400],&size_2[400]);
	printf("size_1[96] data is %u, and addr is %p\n",size_1[96],&size_1[96]);
	while(1);
	return 0;
}










