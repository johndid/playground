#include <cstddef>
#include <exception>
#include <iostream> 
#include <sstream>

using namespace std;

int main (int argc, char** argv) 
{
    enum {success=0x00,failure};
    const int arguments = 1;
    try
    {
	if(arguments < argc) 
	{
	    while(*(argv++) != 0) 
	    {
		cout << *argv << endl;
	    }
	    return success;
	}
	cout << "Hello world" << endl;
	return success;
    }
    catch(ios_base::failure &e) 
    {
    	cerr << "I/O error" << e.what() << endl; 
    }
    return failure;
}
