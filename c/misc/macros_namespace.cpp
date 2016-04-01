#include <stdio.h>

#define ENABLE_STUFF

namespace stuff {
#define ENABLE_STUFF 1
}

int main (int argv, char **argc)
{
    printf("%s",(int)ENABLE_STUFF);
    printf("%s",(int)stuff::ENABLE_STUFF);
}
