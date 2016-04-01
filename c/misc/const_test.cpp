#include <stdio.h>
#include <iostream>

class test {
public:
    test(const int i):num(i){};
    ~test(){};

    const int getnum(){return num;};
    int *ptr_getnum(){return &num;};
    const int *const_ptr_getnum(){return &num;};
    int const *ptr_const_getnum(){return &num;};

    test &reference_test(){return *this;};
    const test &const_reference_test(){return *this;};
    test copy_test(){return *this;};
    test *ptr_test(){return this;};
    const test *const_prt_test(){return this;};
    test const *prt_const_test(){return this;};

private:
    int num;
    static const int const_num=0;
    
};

int main (const int argc, char const * const* argv)
{
    test t(1);

    int i = t.getnum();
    std::cout << i << std::endl;
    std::cout << ++i << std::endl;

//    int *pi = t.const_ptr_getnum(); -fpermissive needs a const cast!!!!

    test t2(2);
    test t3(3);

    t3 = t2.const_reference_test();

    return 0;
}
