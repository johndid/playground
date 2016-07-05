#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/**
 * This function converts a number to its binary representation
 * x is the number you wish to convert 
 */
const char* bytetobinary(int x) {
  static char b[9];
  b[0]='\0';
  for(int j=128;j>0;j>>=1)
    strcat(b,((x & j) == j)? "1" : "0");
  return b;
}

/**
 * This function converts an int to is binary representation in a string.
 * num is the number to convert.
 * The function returns a char pointer to the converted string, remember to copy and free the result
 * when you use the function.
 *
 * please notice that the function i 32 bits meaning any values > 0xffff will fail!
 **/
const char* inttobinary(int num){
  int lsb = htonl(num); /* Order the bytes to follow network order of big endian makes the conversion straight forward */
  char *bytes = (char*)&lsb;
  static char binary[33];
  binary[0]='\0';

  int high = 0;
  for(int jj=0;jj<4;jj++) {
    strcat(binary,bytetobinary(bytes[jj]));
  }
  return binary;
}

/**
 * The following program solves the power off (aka ^ (hat) operator equations)
 * But it also wiggles the xor operation on the passed data, since after all 
 * the meaning of ^ varies. In other words whats the meaning of ^ ... Well as 
 * always the answer is: It depends!
 **/
int main(int argc, char **argv) {

  if(3 == argc) {
    int *equation = malloc(sizeof(int)*argc);
    for(int j=1;j<argc;j++) {
      equation[j] = (int)strtol(argv[j],NULL,10);
    }

    int a=equation[1];
    int b=equation[2];
    int xor=equation[1]^equation[2];
    int p=pow(equation[1],equation[2]);
    char *stra = strdup(inttobinary(a));
    char *strb = strdup(inttobinary(b));
    char *strxor = strdup(inttobinary(xor));
    char *strp = strdup(inttobinary(p));
    
    printf("xor: %d ^ %d = %d (%s ^ %s = %s)\n",a,b,xor,stra,strb,strxor);
    printf("pow: %d ^ %d = %d (%s ^ %s = %s)\n",a,b,p,stra,strb,strp);

    free(equation);
    free(stra);
    free(strb);
    free(strxor);
    free(strp);
  }
  return 0;
}
