#include <iostream>
#include "../include/socket/serverSocket.h"
#include "../include/socket/socketException.h"
#include <string>
using namespace std;

int main ( int argc, char* argv[] )
{
	cout << "running....\n";

	try
	{
		// Create the socket
		ServerSocket server ( 30000 );

		while ( true )
		{

			ServerSocket new_sock;
			server.accept ( new_sock );

			try
			{
				while ( true )
				{
					std::string data;
					new_sock >> data;
					new_sock << data;
				}
			}
			catch ( SocketException& ) {}

		}
	}
	catch ( SocketException& e )
	{
		cout << "Exception was caught:" << e.getMessage() << "\nExiting.\n";
	}

	return 0;
}
