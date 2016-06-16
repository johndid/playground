#include <stdio.h>
#include <stdlib.h>
#include <libfswatch/c/libfswatch.h>

/**
 * The following function implements the callback functionality for testing eventnumber send from the
 * libdawatch library. See FSW_CEVENT_CALLBACK for details.
 */
void my_callback(fsw_cevent const * const events, const unsigned int event_num, void * data) {
  printf("my_callback: %d\n",event_num);
}

int main(int argc, char **argv) {

  //  if(2 <= argc) {
    if(FSW_OK == fsw_init_library()) {

      //      FSW_HANDLE fsw_init_session(const fsw_monitor_type type = system_default_monitor_type);
      /* const FSW_HANDLE handle = fsw_init_session(/\*system_default_monitor_type*\/fsevents_monitor_type); */
      /* if(FSW_INVALID_HANDLE != handle) { */

      /* 	/\* Loop and all all paths passed to the program *\/ */
      /* 	int j = 0; */
      /* 	for(j=1;j<argc;j++) { */
      /* 	  if(FSW_OK != fsw_add_path(handle,argv[j])) { */
      /* 	    fsw_last_error(); */
      /* 	  } */
      /* 	} */

      const FSW_HANDLE handle = fsw_init_session(/*system_default_monitor_type*/fsevents_monitor_type);
      if(FSW_INVALID_HANDLE != handle) {

	/* Loop and all all paths passed to the program */
	//	int j = 0;
	//for(j=1;j<argc;j++) {
	  if(FSW_OK != fsw_add_path(handle,"/Users/cannabissen/Documents/src/bash")) {
	    fsw_last_error();
	  }
	  //}

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
    //  }
//  else {
//    (void)printf("usage: %s [path]\n",argv[0]);
//  }
  return 0;
}
