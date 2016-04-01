#include <deamon/incoming_connection.h>
#include <deamon/client_chat.h>
#include <sockets/server_socket.h>
#include <utilities/converter.h>
#include <utilities/file.h>
#include <engine/engine.h>
#include <iostream>

#include <sys/time.h>

using namespace std;

Incoming_connection_thread::Incoming_connection_thread(Server_socket *const _server,
						       engine *const _engine,
						       service *_query_service,
						       Client_chat_queue_interface* const _chat_queue,
						       const char* _ip,
						       pthread_mutex_t* const mutex) : \
    posix_thread(mutex),
    main_socket_server(_server),
    engine_model(_engine),
    engine_query_service(_query_service),
    chat_thread_queue(_chat_queue),
    server_to_client_socket(NULL),
    ip(_ip)
{
    cout << "Incoming_connection_thread::Incoming_connection_thread" << endl;
    pfd.fd = main_socket_server->get_handle();
    pfd.events = POLLIN;
    main_socket_server->set_non_blocking(true);
}

Incoming_connection_thread::~Incoming_connection_thread()
{
    cout << "Incoming_connection_thread::~Incoming_connection_thread" << endl;
    // there's no need to remove the pointer if it has not been created
    // I know you can say delete to a NULL pointer, but that construction makes
    // the valgrind memory checker puke tons of invalid free/delete messages
    // it can see that you are incorrectly (free|delete)'ing a pointer
    // checking for validity helps the debugger tool and the reads of the code ;)
}

// POLLING DEBUG FUNCTION
// void Incoming_connection_thread::dump_poll(const int poll) 
// {
//   cout << "Incoming_connection_thread::dump_poll" << endl;
  
//   if(poll & POLLIN) {
//     cout << "POLLIN" << endl;
//   }
//   else if(poll & POLLPRI) {
//     cout << "POLLPRI" << endl;
//   }
//   else if(poll & POLLOUT) {
//     cout << "POLLOUT" << endl;
//   }
//   else if(poll & POLLRDHUP) {
//     cout << "POLLRDHUP" << endl;
//   }
//   else if(poll & POLLERR) {
//     cout << "POLLERR" << endl;
//   }
//   else if(poll & POLLHUP) {
//     cout << "POLLUP" << endl;
//   }
//   else if(poll & POLLNVAL) {
//     cout << "POLLNVAL" << endl;
//   }
//   else {
//     cout << "Linux dont's care about this poll value: " << poll << endl;
//   }
// }

void Incoming_connection_thread::run()
{
    // To be able to give the instance overship of the server to client socket connection to the 
    // actual client chat thread (the entity responsible for communication) we need to have an 
    // allocated piece of memory that we can pass.
    // The receiving entity (the client chat thread) is responsible for free'ing the memory again 
    // once it execution stops
    const int retval = poll(&pfd,1,100);
    if(retval > 0) 
    {
	if(pfd.events & POLLIN) 
	{
	    Server_socket *client_connection = new Server_socket();
	    if(main_socket_server->accept(client_connection)) 
	    {
		Client_chat_thread *client_chat_thread = new Client_chat_thread(engine_model, engine_query_service,client_connection, chat_thread_queue,ip,owner_mutex);
		if(client_chat_thread)
		{
		    client_chat_thread->start();
		    engine_model->add_client(converter::int2string(client_connection->get_handle()),client_connection->get_addr());
		}
		else 
		{
		    cout << "Client thread not created!" << endl;
		}
	    }
	    else
	    {
		delete client_connection;
	    }
	}
    }
}

const bool Incoming_connection_thread::start()
{
    return posix_thread::start();
}

const int Incoming_connection_thread::stop()
{
    // to be able to shutdown correctly we'll have to shut teh main socket down before stopping
    // The thread must be join in the owner
    main_socket_server->shutdown();
    const int ret = posix_thread::stop();
    main_socket_server->close();
    return ret;
}
