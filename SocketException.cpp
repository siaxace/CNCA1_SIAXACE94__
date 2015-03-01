#include "SocketException.h"

SocketException::SocketException(string m){
	message = m;	
}

string SocketException::getMessage(){
	return message;
}
