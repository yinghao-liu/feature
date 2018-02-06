#ifndef _CURL_BUILDER_
#define _CURL_BUILDER_
#include <iostream>
#include <string>
#include <curl/curl.h>
class curl_t{
public:
	~curl_t();
	int init();	
	int get_url(const char *url);
	int post_url(const char *url);
protected:
	static size_t receive_data(char *ptr, size_t size, size_t nmemb, void *userdata);

private:
	CURL *curl_handle = NULL;
	std::string buff;

	
};

#endif
