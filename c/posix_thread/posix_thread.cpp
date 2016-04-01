#include "posix_thread.h"
#include <iostream>
#include <stdlib.h>
#include <errno.h>

using namespace std;

posix_thread::posix_thread():running(false),owner_mutex(NULL),type(detached)
{
  (void)posix_thread::init_mutex(&my_mutex); // TODO: consider throwing exceptions when mutex locking fails!
}

posix_thread::posix_thread(const thread_type _type):running(false),owner_mutex(NULL),type(_type)
{
  (void)posix_thread::init_mutex(&my_mutex); // TODO: consider throwing exceptions when mutex locking fails!
}

posix_thread::posix_thread(pthread_mutex_t *mutex):running(false),owner_mutex(mutex),type(detached)
{
  (void)posix_thread::init_mutex(&my_mutex); // TODO: consider throwing exceptions when mutex locking fails!
}

posix_thread::~posix_thread() 
{
  (void)posix_thread::destroy_mutex(&my_mutex);
}

const bool posix_thread::start() 
{
  if(!running) {
    running = true;
    if(0 == ::pthread_create(&thread, NULL, posix_thread::start_thread, (void*)this)) {
      return true;
    }
    cerr << "posix_thread::start -> failed - Couldn't start the thread" << endl;
  }
  return false;
}

const int posix_thread::stop() 
{
  cout << "posix_thread::stop() " << thread << endl;
  if(running) {
    running = false;
    if(detached == type) {
      const int ret = ::pthread_detach(thread);
      if(0 != ret) {
	dump_err(ret);
      }
    }
  }
  return 0;
}

void *posix_thread::start_thread(void *obj)
{
  // format the function pointer from the pthread.h library
  // enabling it to call the internal running method
  if(obj) {
    reinterpret_cast<posix_thread*>(obj)->run_till_stop();
  }
  return NULL;
}

void posix_thread::run_till_stop() 
{
  // execute the thread's run method until it is stopped
  // then delete the thread!
  while(running) {
    run();
  }
}

const bool posix_thread::lock(pthread_mutex_t* const mutex) 
{
  const int err = ::pthread_mutex_lock(mutex);
  if(0 == err) {
    return true;
  }
  return false;
}

const bool posix_thread::unlock(pthread_mutex_t* const mutex) 
{
  const int err = ::pthread_mutex_unlock(mutex);
  if(0 == err) {
    return true;
  }
  return false;
}

const bool posix_thread::init_mutex(pthread_mutex_t* const mutex) 
{
  if(0 == ::pthread_mutex_init(mutex,NULL)) {
    return true;
  }
  return false;
}

const bool posix_thread::destroy_mutex(pthread_mutex_t* const mutex)
{
  if(0 == ::pthread_mutex_destroy(mutex)) {
    return true;
  }
  return false;
}

const bool posix_thread::join(pthread_t id) 
{
  const int ret = ::pthread_join(id,NULL);
  if(0 == ret) {
    return true;
  }
  posix_thread::dump_err(ret);
  return false;
}

void posix_thread::dump_err(const int err) 
{
  switch(err) {
  case EDEADLK: cerr << "posix_thread::dump_err -> EDEADLK" << endl; break;
  case EINVAL: cerr << "posix_thread::dump_err -> EINVAL" << endl; break;
  case ESRCH: cerr << "posix_thread::dump_err -> ESRCH" << endl; break;
  default: cerr << "posix_thread::dump_err -> unknown" <<endl; break;
  }
}
