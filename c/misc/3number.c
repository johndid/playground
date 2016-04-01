#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, const char * argv[])
{
    int input = 0;
    char* output = 0;
    int i=0;

    //REVIEW: printf should check the return value andf bajdghahklgfkgaskf
    printf("%s","Please enter a number:\n");
    scanf("%d",&input);
    output = (char*)malloc((size_t)input+1);
    memset(output,0,input+1);
    for(;i<input;i++)
    {
        output = strcat(output,"*");
        puts(output);
    }
    printf("%d\n",(input*(input+1))/2);
    free(output);
    //REVIEW: program shoud only retrun success whenlhsglsghk
    return 0; 
}
