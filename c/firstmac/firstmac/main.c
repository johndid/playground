#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, const char * argv[])
{
    int input = 0;
    char* output = 0;
    int i=0;

    printf("%s","Please enter a number:\n");
    scanf("%d",&input);
    input = (0<input)?input:(input*(-1));
    if(input < (INT_MAX/2))
    {
        if(input <= 80)
        {
            output = malloc(input+1);
            memset(output,0,input+1);
            for(;i<input;i++)
            {
                output = strcat(output,"*");
                puts(output);
            }
            free(output);
        }
        else{
            printf("Stars won't fit your terminal!\n");
        }
    }
    printf("Triangular number is: %d",(input*(input+1))<<2);
    return 0;
}

