#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

/// These are the programs exit reasons
enum exit_values 
{
    success = EXIT_SUCCESS, ///< Need I say more?
    bad_option_passed, ///< incorrect opion passed to the program
    engine_folder_error ///< The switchboard engine model folder is not present, or you do not have permoissions to write
};

/// the usage function prints the switchboards usage string.
void usage() 
{
    cout << "switchboard [option] argument" << endl;
    cout << "where:" << endl;
    cout << "-d domain optional argument will use $hostname if not present! " << endl;
    cout << "-e engine dir optional argument, will use /engine if not present. But the actual drive must be present or the program will fail." << endl;
    cout << "-h hostname optional argument will use $hostname if not present" << endl;
    cout << "-l logfile optional argument, will use switchboard.log if not present" << endl;
    cout << "-p port optional argument will use 8080 if not present" << endl;
}

/// The parse options function, extracts the arguments as given from the command line
/// Each argument for the switchboard is passed to the function, for creation
/// The individual argument have different meanings and must be checked against these.
///
/// all arguments are optional, and if not passed they'll obtain a default argument value
/// see the usage function for details!
///
/// @param argc int as presented by the main() function
/// @param argv char ** as presented by the main() function
/// @param host string to fill with the host name
/// @param domain string to fill with the domain
/// @param post string tp fill withe the port number
/// @param engine string to fill with the engine folder
/// @param log string to fill with the log file
/// @return true if the options are passed correctly, false if there is an error
bool parse_program_options(int argc,char ** argv,string &host, string &domain, string &port, string &engine, string &log)
{
    // argument string for the getopt function, containing all legal options
    // the arguments follow the options explained above, the : is used by
    // getopt to indicate the the option needs an tailing argument
    // i.e. -h hostname 
    const char *switchboard_options = "h:e:l:p:d:"; // lmao
    int c; // temporary place holder used to extract the individual options with getopt, see: man getopt for details
    char len=80; // buffer length, used with buffer, to extract host and domain names from the machiene running the application
    char buffer[len]; 

    // read the machiene defaults for host and domain! These should be overwritten with care
    // as the switchboard should use the machiene name and current domain for this
    // The switchoard uses these values in the replies to its clients. They are 
    // inserted into the XML messages in the <!DOCTYPE/> tag to allow clients to validate
    // against the DTD's served by the switcboard
    if(0 == gethostname(buffer,len)) host = string(buffer);
    if(0 == getdomainname(buffer,len)) domain = string(buffer);

    opterr = 0;
    while ((c = getopt(argc, argv, switchboard_options)) != -1)
    {
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
        /* Fall through */
	default:
	    return false;
	}
    }
    return true;
}

/// This function checks the existance of the engine model folder, and returns false if the folder does not
/// exist, or if the program does not have permissions to change the folder!
/// @param engine folder path
/// @return true if the engine folder exists and the program have permissions to write in it, false if not
bool check_engine_folder(const string& engine)
{
    struct stat sb;
    if(-1 < stat(engine.c_str(),&sb))
    {
	if(S_IFDIR == (sb.st_mode & S_IFMT))
	{
	    if (0 == access(engine.c_str(),F_OK|R_OK|W_OK|X_OK))
	    {
		return true;
	    }
	    else
	    {
		cout << "process: " << getpid() << " don't have permissions to access: " << engine.c_str() << endl;
	    }
	}
	else
	{
	    cout << engine.c_str() << "Is not a directory!" << endl;
	}
    }
    return false;
}
     
int main (int argc, char **argv)
{
    string domain, host, engine("/engine/"), port("8080"), log("switchboard.log");
    if(parse_program_options(argc,argv,host,domain,port,engine,log))
    {
	if(check_engine_folder(engine))
	{
	    cout << "switchboard@" << host.c_str() << "."<< domain.c_str() << ":" << port.c_str() << engine.c_str() << endl;
	    cout << "logging to: " << log.c_str() << endl; 
	    return success;
	}
	return engine_folder_error;
    }
    return bad_option_passed;
}
