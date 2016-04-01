#ifndef Incoming_connection_thread_h_
#define Incoming_connection_thread_h_

#include <utilities/thread.h>
#include <sys/poll.h>

class Server_socket;
class engine;
class service;
class Client_chat_queue_interface;

/// The incoming connection thread class handles socket::accept()'anse from incoming client requests.
/// It is responsible for creating new Client_chat_threads upon succesfull server_socket::accept()'ance
/// 
/// Inheritance to the posix_thread class is public because the switchboard (the owner of this class instance) 
/// must be able to call the stop method, inorder to terminate this thread. This functionality is needed
/// for the switchboard to hand back the resources occupied by this class instance.
class Incoming_connection_thread : public posix_thread
{
 public:
  /// Constructor .
  /// @param sckt Server_socket pointer to the main serving socket, constness must be kept as this pointer should be undeletable from this class
  /// @param eng engine pointer to engine model, constness must be kept as this pointer should be undeletable from this class
  /// @param ser service pointer to the engine query service,constness must be kept as this pointer should be undeletable from this class
  /// @param queue Client_chat_queue_interface pointer to the client chat queue, constness must be kept as this pointer should be undeletable from this class
  /// @param ip string containing the host ip address
  /// @param mtx pthread_mutex_t to lock against
  Incoming_connection_thread(Server_socket *const sckt, engine *const eng, service *const ser, Client_chat_queue_interface* const queue,const char* ip,pthread_mutex_t* const mtx);
  ~Incoming_connection_thread();

  /// This function is the threads run method. It is overwritten and publicised for the switchboard to control
  /// @return true while the thread runs, false when it has been stopped
  virtual void run(); 
  virtual const bool start(); ///< incoming connection special edition of start, see posix_thread::start for details
  virtual const int stop(); ///< incoming connection special edition of start, see posix_thread::stop for details

 private:
  Server_socket* const main_socket_server; ///< this member contain the main socket, that accepts connections from switchboard clients
  engine* const engine_model; ///< This member is the engine model, it is neded to feed client_chat_threads with the engine_model
  service* const engine_query_service; ///< This member is the wngine query service, it is neded to feed client_chat_threads with the engine_model

  /// This member is the client chat queue interface, it is neded to feed client_chat_threads with the engine_model
  Client_chat_queue_interface* const chat_thread_queue;

  Server_socket* server_to_client_socket; ///< This member holds the socket connection to the client
  const char* ip; ///< This member holds the host ip address
  pollfd pfd; ///< This member is the poll structure, that is used to poll the socket with
};

#endif //Incoming_connection_thread_h_
