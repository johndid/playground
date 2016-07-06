#include <stdio.h>
#include <stdlib.h>
#include <libfswatch/c/libfswatch.h>

/**
 * To compile this program you'll have to link against libfswatch to sort any issues with dunamic references
 * Remember to use a dynamic library i.e.
 * $ gcc -I /usr/local/include -o "fswatch_test" fswatch_test.c /usr/local/lib/libfswatch.dylib 
 * 
 * You run the program like this:
 * $ ./fswatch_test ../bash/
 *
 * The only output is callback for now, but you can update it as you please, its meant for testing the c compilation and linkage
 * in a c enviroment.
 **/

/**
 * The following function implements the callback functionality for testing eventnumber send from the
 * libdawatch library. See FSW_CEVENT_CALLBACK for details.
 */
void my_callback(fsw_cevent const * const events, const unsigned int event_num, void * data) {
  printf("my_callback: %d\n",event_num);
}

int main(int argc, char **argv) {

  if(2 <= argc) {
    if(FSW_OK == fsw_init_library()) {

      const FSW_HANDLE handle = fsw_init_session(fsevents_monitor_type);
      if(FSW_INVALID_HANDLE != handle) {

	/* Loop and all all paths passed to the program */
	int j = 0;
	for(j=1;j<argc;j++) {
	  if(FSW_OK != fsw_add_path(handle,argv[j])) {
	    fsw_last_error();
	  }
	}

	if(FSW_OK != fsw_set_callback(handle, my_callback,NULL)) {
	  fsw_last_error();
	}

	fsw_set_allow_overflow(handle,0);
	
	if(FSW_OK != fsw_start_monitor(handle)) {
	  fsw_last_error();	  
	}
      }
      else {
	fsw_last_error();
	(void)printf("Invalid fswatch handle: %d\n",handle);	
      }
    }
    else {
      fsw_last_error();	  
      (void)printf("fswatch cannot be initialised!\n");
    }
  }
  else {
    (void)printf("usage: %s [path]\n",argv[0]);
  }
  return 0;
}
