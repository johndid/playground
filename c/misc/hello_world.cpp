#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
    cout << "hello world" ;
    for(int i=0;i<argc;i++) {
	
	cout << argv[i] << std::endl; 

    }
    return 0;
}
