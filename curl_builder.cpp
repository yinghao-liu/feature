#include "curl_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
curl_t::~curl_t()
{
	curl_easy_cleanup(curl_handle);	
}

int curl_t::init()
{
	curl_handle = curl_easy_init();
	if (NULL == curl_handle){
		return -1;
	}
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&buff);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, receive_data);
}
size_t curl_t::receive_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	string *data = (string *)userdata;
	data->append(ptr, size*nmemb);
}
int curl_t::post_url(const char *url)
{
	CURLcode code;

	curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	buff.clear();
	/*add head information*/
	struct curl_slist *slist=NULL;
	slist = curl_slist_append(slist, "yinghao:francis");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist);
	/*post data*/
	string aa="hahahahhahhahahah";
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, (void*)aa.c_str());
	/*perform*/
	code = curl_easy_perform(curl_handle);
	if (0 != code){
		printf("curl_easy_perform error\n");
	}
	curl_slist_free_all(slist);
	return 0;
}

int curl_t::get_url(const char *url)
{
	CURLcode code;

	curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	buff.clear();
	/*add head information*/
	struct curl_slist *slist=NULL;
	slist = curl_slist_append(slist, "yinghao:francis");
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, slist);
	/*perform*/
	code = curl_easy_perform(curl_handle);
	if (0 != code){
		printf("curl_easy_perform error\n");
	}
	curl_slist_free_all(slist);
	//cout<<buff<<endl;
	cout<<"buff len is "<<buff.size()<<endl;
	return 0;
}

