#ifndef __SIAMOZ__CLIENTSOCKET
#define __SIAMOZ__CLIENTSOCKET

// Definition of the ClientSocket class


#include "socket.h"


class ClientSocket : private Socket
{
	public:

		ClientSocket ( std::string host, int port );
		virtual ~ClientSocket(){};

		const ClientSocket& operator << ( const std::string& ) const;
		const ClientSocket& operator >> ( std::string& ) const;

};


#endif
