//#include <sys/types.h>
//#include <sys/stat.h>
//#include <dirent.h>
//#include <unistd.h>
#include <string.h>
// #include <iostream>
#include <stdio.h>
#include <stdlib.h>

//using namespace std;

int main(int argc, char** argv)
{
 int i;
 
// cout << argc << endl;
    printf("%d",argc);

// cout << &argv[0] << endl;
// cout << &argv[1] << endl;
// cout << &argv[2] << endl;


 for(i=0;i<argc;i++)
 {
//     cout << "argv[" << i << "]" << "@" << &argv[i] << ":" << argv[i]<< endl;
     printf("argv[%d]@%X:%s\n",i,(unsigned int)&argv[i],argv[i]);
 }

// cout << "------------------------" << endl;
// cout << "argv[1] gets assigned after this" << endl;
// cout << "------------------------" << endl;

 printf("------------------------\n");
 printf("argv[1] gets assigned after this\n");
 printf("------------------------\n");

 if (argc != 2)
 {
     argv[1] = "john skriver en psykopat lang text";
 }    

// cout << argv[1] << endl;
 printf("%s\n",argv[1]);

 for(i=0;i<argc;i++)
 {
//     cout << "argv[" << i << "]" << "@" << &argv[i] << ":" << argv[i]<< endl;
     printf("argv[%d]@%X:%s\n",i,(unsigned int)&argv[i],argv[i]);
 }

 return 0;
}
