#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

int main(int argc, const char * argv[])
{
  const char* text = "I'll calculate the trianular number for the number you enter faggot:\n";
  int exit = 1;
 faggot:
  if(strlen(text) == (size_t)printf("%s",text))
    {
      int input = 0;
      if(0 < scanf("%d",&input))
	{
	  if(input < 0)
	    {
	      input*=-1;
	    }

	  if( 0 == input || input > INT_MAX )
	    {
	      if(-1 < printf("I know %d is a number faggot! But it not worth wasting cycles on! Try again\n",input))
		{
		  goto faggot;
		}
	    }
	  else
	    {
	      const int num_chars_in_term = 80;
	      const int triangular = (input*(input+1))/2;

	      if(input <= num_chars_in_term)
		{
		  if( -1 < printf("The triangular number for %d is %d, which you'll see illustrated below in *\n",input,triangular))
		    {
		      char* output = (char*)malloc((size_t)input+1);
		      if(output)
			{
			  int i=0;
			  memset(output,0,(size_t)input+1);
			  for(;i<input;i++)
			    {
			      strcat(output,"*");
			      if(-1 < puts(output))
				{
				  exit=0;
				}
			      else 
				{
				  break;
				}
			    }
			  free(output);
			}
		    }
		}
	      else
		{
		  if( -1 < printf("The triangular number for %d is %d, No starts for you faggot! They wont be pretty printed!\n",input,triangular)){};
		}
	    }
	}
    }
  return exit;
}


