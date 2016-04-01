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

    // float formatting
    // set precision must be set when reading the numerical value into the stream object, it uses all values, not just the 
    // ones after the .dot
    float f;
    o << setprecision (7) << 121234.56789;
    o >> f;

    cout << "float(none):\t\t" << noshowpoint << f << endl;
    cout << "float(none) showpoint:\t" << showpoint << f << endl;

    cout.precision(9);
    cout << "float(none):\t" << f << endl;
    cout << "fixed:\t\t" << fixed << f << endl;
    cout << "scientific:" << scientific << '\t' << f << endl;
    o.clear();

    // boolean formatting
    bool b;
    o << false;
    o >> b;
    cout << "none:\t\t" << b << endl;
    cout << "boolalpha:\t" << boolalpha << b << endl;
    cout << "noboolalpha:\t" << noboolalpha << b << endl;
    o.clear();
    
    // integer formatting
    int i;
    o << 40;
    o >> i;
    cout << "hex:\t" << hex << i << endl;
    cout << "hex:\t" << hex << uppercase << i << endl;
    cout << "dec:\t" << dec << i << endl;
    cout << "oct:\t" << oct << i << endl;
    o.clear();
    o << hex << 32;
    o >> i;
    cout << "hex:\t" << hex << i << endl;
    cout << "dec:\t" << dec << i << endl;
    cout << "oct:\t" << oct << i << endl;
    o.clear();

    // string conversion
    o << dec << "24.12"; // notice that the stream keeps the formatter hex was set as a test above
    o >> f;
    cout << "f=" << fixed << f << endl;

    string s(o.str());
    cout << "s=" << s.c_str() << endl;

    return success;
}
