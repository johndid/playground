#include <stdio.h>
#include <memory.h>

int main(int argc, const char * argv[])
{
    int input = 0;
    char* output = 0;
    int i=0;

    printf("%s","Please enter a number:\n");
    scanf("%d",&input);
    output = malloc(input+1);
    memset(output,0,input+1);
    for(;i<input;i++)
    {
        output = strcat(output,"*");
        puts(output);
    }
    printf("%d",(input*(input+1))/2);
    free(output);
    return 0;
}
