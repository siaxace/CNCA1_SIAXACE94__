#ifndef __SIAMOZ__ServerSocket
#define __SIAMOZ__ServerSocket

// Definition of the ServerSocket class

#include "socket.h"


class ServerSocket : private Socket
{
	public:

		ServerSocket ( int port );
		ServerSocket (){};
		virtual ~ServerSocket();

		const ServerSocket& operator << ( const std::string& ) const;
		const ServerSocket& operator >> ( std::string& ) const;

		void accept ( ServerSocket& );

};


#endif
