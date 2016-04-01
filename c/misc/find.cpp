#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const bool find(vector<string> &find_results, const std::string &path,const std::string &search_pattern,vector<string> &exclude_pattern,const bool exclude)
{
    DIR *d;
    if((d = ::opendir(path.c_str()))) 
    {
	struct dirent *entry;
	struct stat statbuf;

	while((entry = ::readdir(d)) != NULL) 
	{
	    ::lstat(entry->d_name,&statbuf);
	    if(S_ISDIR(statbuf.st_mode)) 
	    {
		exclude_pattern.push_back(".");
		exclude_pattern.push_back("..");
		vector<string>::iterator it = exclude_pattern.begin();
		for(; it != exclude_pattern.end();it++)
		{
		    string dir(*(it));
		    // ignore the entries in the exclude_pattern
		    if(strcmp(dir.c_str(),entry->d_name) == 0)
		    {
			continue;
		    }
		    else 
		    {
			find_results.push_back(string(entry->d_name));
		    }
		}
	    }
	}
	::closedir(d);
	return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    vector<string> exclude_path;
    vector<string> find_results;
    string engine_path("/engine/");
    string expression("outvar");

    if(find(find_results,engine_path,expression,exclude_path,true))
    {
	vector<string>::iterator it = find_results.begin();
	for(;it != find_results.end();it++)
	{
	    cout << "Found: " << string(*(it)).c_str() << endl;
	}
    }
    else
    {
	cout << "Found nuttin nigga!!" << endl;
    }

    return 0;
}
