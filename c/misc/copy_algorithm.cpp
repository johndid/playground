#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main (int argc,char** argv)
{
    char buf[] = {'p','a','r','t','1','\0','p','a','r','t','2','\0','p','a','r','t','3','\0'};
    vector<char> rawdata(buf,buf + sizeof(buf)/sizeof(*buf));

    vector<string>queue;
    vector<char>::iterator it;
    string s;
    for(it = rawdata.begin();it != rawdata.end();it++ )
    {
    	if(*it == '\0')
    	{
    	    queue.push_back(s);
	    s="";
    	}
	else
	{
	    s.insert(s.end(),*it);
	}
    }

    vector<string>::iterator qit;
    for(qit = queue.begin() ; qit != queue.end();qit++)
    {
    	cout << string(*(qit)).c_str() << endl;
    }

    return 0;
}
