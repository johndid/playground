//#include <bes/unittest/unittest.h>
#include <stdint.h>
 
uint16_t swap(uint16_t x) { return x;};
uint32_t swap(uint32_t x) { return x;};
uint64_t swap(uint64_t x) { return x;};
 
int main(int argc,char** argv)
{
    unsigned int y = 0;
    swap(y);
}
