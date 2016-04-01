#include <cstddef>
#include <exception>
#include <iostream> 
#include <iomanip>
#include <sstream>


using namespace std;

int main (int argc, char** argv) 
{
    enum {success=0x00,failure};

    stringstream o;
    float f;

    o << 12.123456789;
    o << 2;
    o << true;
    o << "john";

    cout << "stringstream.str(): " <<  o.str() << endl;

    o >> f >> i >> b;

    cout << fixed << "fixed:" << (f*10) << endl;
    cout << setprecision  (3 )<< "float:" << (f*10) << endl;
    cout << setprecision (1 )<< "float:" << (f*10) << endl;
    cout << setprecision (8 )<< "float:" << (f*10) << endl;

    return success;
}
