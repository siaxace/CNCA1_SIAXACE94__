#ifndef __SIAMOZ__SocketExeption
#define __SIAMOZ__SocketExeption

#include <string>
using namespace std;

class SocketException {
	public:
		SocketException(string m);
		string getMessage();
	private:
		string message;
};


#endif
