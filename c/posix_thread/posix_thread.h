#ifndef posix_thread_h_
#define posix_thread_h_

#include <pthread.h>

///@b posix_thread
///This class is the interfcae to the posix threads
///This file is an interface to the posix threads, the file wraps the pthread.h library into a simple to use
///c++ class.
///
///NOTICE:
///Not all pthread functionality has been added to the class, if there's something missing feel free to add the missing parts,
///
///The class contains two functions that should be used from the code wishing to start and stop the thread,
///These are the start() and stop() methods.
///
///On creation the posix_thread will not be started, it will be instanciated. When start() is called the thread will start running
///This means that the run method will be executed.
///
///The run() method is running inside a loop that can only be stopped by calling stop. So, until the stop call is send the thread will
///continue to run.
///
///If the thread object instance goes out of scope, the posix_thread will automatically call stop (from it's destructor) and the thread
///will be stopped
///
///To use this class you'll have to derive a new class that implements the functionality that you need to have in your thread.
///Simply, override the run() method. There's no need to create a while(1) statement inside your over written method in the derived class
///as the run() method is already inside a loop.
///
///However, The run() method returns a boolean. When the run() method returns false, it means that the thread has stopped,
///without stop being called. If the run() is returning true, means keep on running!
///
///The class automatically has a mutex added to the thread, so all you have to do is call the lock() and unlock() methods where you need
///to ensure that other threads does not access the shared data
class posix_thread 
{
 public:
  enum thread_type {
    joinable = 0x00, ///< Joinable enables the thread to be synchronized, meaning you can wait until it finishes
    detached, ///< Detached means that the thread runs autonomously
  };

  posix_thread();

  // TODO: do we need to have both types of threads?!?! or is the mutex and joinable enough ???
  /// This constructor creates a thread from it's type
  /// @param _type thread_type to create the threda against
  posix_thread(const thread_type _type);

  /// This constructor creates a thread that uses it's owners mutex to lock against
  /// @param owner_mutex ptherad_mutex_t that the therad should use to lock critical sections against
  posix_thread(pthread_mutex_t* const owner_mutex);
  
  ///@b start 
  ///This function starts the thread
  ///@return true if the thread was started, false if not / or false when the thread has been started!
  virtual const bool start();
  
  ///@b stop
  ///@return int which is the return value from the thread start function, this will be ZERO!
  virtual const int stop();

  pthread_t id() { return thread; }; ///< This function returns the thread handles id 

  /// This function is used to initialize a mutex
  /// @param mtx a pthread_mutex_t object to initialize
  /// @return true when initialization is a undisputed success, false when it fails dramatically
  static const bool init_mutex(pthread_mutex_t* const mtx);

  /// This function is used to destroy an existing mutex
  /// @param mtx a pthread_mutex_t object to initialize
  /// @return true when initialization is a undisputed success, false when it fails dramatically
  static const bool destroy_mutex(pthread_mutex_t* const mtx);

  ///@b lock
  ///This function adds a mutex lock on the thread
  /// @param mtx a pthread_mutex_t object to lock
  static const bool lock(pthread_mutex_t* const mtx);

  ///@b unlock
  ///This function removes a mutex lock on the thread
  /// @param mtx a pthread_mutex_t object to unlock
  static const bool unlock(pthread_mutex_t* const mtx);

  /// @b join
  /// This function waits for the thread with the specified id to finish
  /// @param thrd pthread_t hnadle to join
  static const bool join(pthread_t thrd);

 protected:
  virtual ~posix_thread();

  ///@b run
  ///This function runs while the trhead is running. Use it to place the functionality that you need
  ///while the thread is active
  virtual void run()=0; // override this function to get your own stuff going while the thread runs!

  /// @b dump_err
  /// This is a debugging function used to dump the thread error code. See: man pthread for details
  /// @param err error number of the pthread interface to dump
  static void dump_err(const int err);
  
  ///@b start_thread
  ///This function is the one needed to create a thread inside the pthread.h library
  ///it needs to be static to ensure that the footprint of the class memberfunction
  /// is the same as for a standard C function pointer.
  ///
  ///@param obj void pointer containing the instanciated objects "this" pointer.
  ///@return NULL 
  static void *start_thread(void *obj); // this function is needed to be able to activate the c style create thread call with the class and other stuff
  
  ///@b run_till_stop
  ///This function is the internal run function that keeps the overvritten function inside a loop until stop is called
  void run_till_stop(); // the function that actually runs the thread in a until stopped loop!
    
  volatile bool running; ///< This member is true while running, and false when stopped. It is there to ensure that you cannot start the thread more than once
  pthread_mutex_t my_mutex; ///< This is the thread's own mutex lock used to lock the thread's data that may be shared with sub threads
  pthread_mutex_t *owner_mutex; ///< This is the thread's owner's mutex lock used to lock for things that are shared with the owner
  thread_type type; ///< This member contain the posix thread type, see thread_type for details
  pthread_t thread; ///< This is the actual thread
};

#endif // thread_h_
