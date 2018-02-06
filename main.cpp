#include "log.h"
#include "curl_builder.h"
#include <curl/curl.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

/********************version***************************/
inline void show_version(void)
{
	    /*VERSION is a macro, defined in Makefile*/
	    printf("%s\n",VERSION);
}

int main(void)
{
	//const char *uri = "https://www.bing.com";
	const char *uri = "http://www.qq.com";
	curl_t curl;
	if (-1 == curl.init()){
		return -1;
	}
	int ret=-1;
	ret = curl.get_url(uri);
	printf("main ret is %d\n", ret);
	return 0;
}

