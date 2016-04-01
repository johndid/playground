#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;
     
int main (int argc, char **argv)
{
/*
  -e engine dir optional argument, will use /engine if not present. But the actual drive must be present or the program will fail.
  -d domain optional argument will use $hostname if not present! 
  -h hostname optional argument will use $hostname if not present
  -l logfile optional argument, will use switchboard.log if not present
  -p port optional argument will use 8080 if not present
*/
    const char *switchboard_opotions = "e:d:h:l:p:";
    int c;
    char len=80;
    char buffer[len];
    string domain;
    string host;
    string engine("/engine/");
    string port("8080");
    string log("switchboard.log");

    if(0 == gethostname(buffer,len)) host = string(buffer);
    if(0 == getdomainname(buffer,len)) domain = string(buffer);

    opterr = 0;
    while ((c = getopt(argc, argv, legal_arguments)) != -1)

 	switch (c)
	{
	case 'e':
	    engine = string(optarg);
	    break;
	case 'd':
	    domain = string(optarg);
	    break;
	case 'h':
	    host = string(optarg);
	    break;
	case 'l':
	    log = string(optarg);
	    break;
	case 'p':
	    domain = string(optarg);
	    break;
	case '?':
	    if (optopt == 'd' || optopt == 'e' || optopt == 'h' || optopt == 'l' || optopt == 'p')
	    {
		printf("Option -%c requires an argument.\n", optopt);
	    }
	    else if (isprint (optopt))
	    {
		printf("Unknown option `-%c'.\n", optopt);
	    }
	    else
	    {
		printf("Unknown option character `\\x%x'.\n", optopt);
	    }
	    return 1;
	default:
	    abort ();
	}

    cout << "switchboard@" << host.c_str() << "."<< domain.c_str() << ":" << port.c_str() << engine.c_str() << endl;
    cout << "logging to: " << log.c_str() << endl; 
    return 0;
}
