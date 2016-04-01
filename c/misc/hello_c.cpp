#include <stdio.h>
#include <string.h>

enum {success=0x00,failure};

int output(char *text)
{
    return (strlen(text) == printf("%s\n",text)) ? success : failure;
}

int dump(int start, int end, char** txt)
{
    int i;
    for(i=start;i<end;i++)
    {
	if(!output(txt[i]) ) 
	{
	    return failure;
	}
    }
    return success;
}

int main (int argc, char** argv)
{
    int arguments = 1;
    return (arguments<argc) ?  dump(arguments,argc,argv) : output((char*)"Nothing to see here, move along!");
}
