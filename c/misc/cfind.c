#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){
   int fds[2];
   char buffer[4096];

   if(pipe(fds) == -1){
      perror("pipe creation failed");
      exit(1);
   }

   switch (fork()){

    case 0://child
       close(fds[0]);
//       execl("/usr/bin/find","find",argv[1], "-name \"*.c\", -print0,NULL);
       execl("/usr/bin/find", "find", 
	     argv[1], 
	     "-name",
	     "*.c", /* As no shell is invoked no quotation marks are needed to protect the *. */
//	     "-print0",  
      (char *) NULL);
       perror("find failed");
       exit(20);
       break;

      case -1: //fork failure
       perror("fork failure");
       exit(1);

      default: //parent
       close(fds[1]); //close stdin so only can do stdout
       int size= read(fds[0],buffer, 4096);
       /* for(int i=0;i<4096;i++) */
       /* { */
	   
       /* } */
       printf("%s",buffer);
   }

   exit(1);
}
