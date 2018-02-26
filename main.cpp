#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

#define MAPFILE      "mapfile"
int parser_companyfile(map<string, string> &apmac_map)
{
	struct stat modify;
	static time_t last_modify=0;
	if (-1 == stat(MAPFILE, &modify)){
		perror("stat MAPFILE");
		return -1;
	}
	if (last_modify == modify.st_mtime){
		printf("not been modified\n");
		return 0;
	}

	last_modify = modify.st_mtime;

	char line[4096]={0};
	char tmp[2][125]={0};
	FILE *fd;
	fd = fopen(MAPFILE, "r");
	if (NULL == fd){
		perror("open MAPFILE");
		return -1; 
	}   
	apmac_map.clear();
	string s1,s2;
	while(NULL != fgets(line, sizeof (line), fd)){
		sscanf(line, "%*[^\t]\t%[^\t]\t%[^\t]", tmp[0], tmp[1]);
		if (0 == strlen(tmp[0])){
			continue;
		}   
		if (0 == strlen(tmp[1])){
			strcpy(tmp[1], "000000");
		}
		s1 = tmp[0];
		s2 = tmp[1];
		apmac_map.insert(make_pair(s1, s2));
		memset(tmp[0], 0, sizeof (tmp[0]));
		memset(tmp[1], 0, sizeof (tmp[1]));
	}   
	fclose(fd);
	return 0;

}

int main(void)
{
	map<string, string> mapp;
	parser_companyfile(mapp);
	parser_companyfile(mapp);
	map<string, string>::iterator iter;
	for (iter=mapp.begin(); iter!=mapp.end(); iter++){
		cout<< iter->first << " => " << iter->second << endl;
	}
	return 0;
}
