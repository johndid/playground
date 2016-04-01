#include <stdio.h>

struct john {
    char variable1;
    unsigned long int variable2;
};

int main()
{
    john dideriksen;
    dideriksen.variable1 = 1;
    dideriksen.variable2 = 2;
    printf("sizeof(dideriksen): %d\n",sizeof(dideriksen));
    printf("sizeof(john): %d\n",sizeof(john));
    printf("sizeof(dideriksen.variable1): %d\n",sizeof(dideriksen.variable1));
    printf("sizeof(dideriksen.variable1 type): %d\n",sizeof(char));
    printf("sizeof(dideriksen.variable2): %d\n",sizeof(dideriksen.variable2));
    printf("sizeof(dideriksen.variable2 type): %d\n",sizeof(unsigned long int));
    printf("dideriksen.variable1: %d\n",dideriksen.variable1);
    printf("dideriksen.variable2: %lu\n",dideriksen.variable2);

    return 1;
};
