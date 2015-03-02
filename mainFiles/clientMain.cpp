#include "../include/socket/clientSocket.h"
#include "../include/socket/socketException.h"
#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
	try
	{

		ClientSocket client_socket ( "localhost", 30000 );

		std::string reply;

		try
		{
			client_socket << "Test message.";
			client_socket >> reply;
		}
		catch ( SocketException& ) {}

		std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.getMessage() << "\n";
	}

	return 0;
}
