lnkOpt  	=       -O3 -Wall
cmpOpt  	=       $(LnkOpt) -c -g

socketCodesDir	=	socketCodes
mainFilesDir	=	mainFiles
socketHeadersDir=	include/socket

all: serverMain.out clientMain.out
	#Done!

serverMain.out: $(mainFilesDir)/serverMain.o $(socketCodesDir)/serverSocket.o $(socketCodesDir)/socketException.o $(socketCodesDir)/socket.o
	g++ $(LnkOpt) $(mainFilesDir)/serverMain.o $(socketCodesDir)/serverSocket.o $(socketCodesDir)/socketException.o $(socketCodesDir)/socket.o -o serverMain.out

clientMain.out: $(mainFilesDir)/clientMain.o $(socketCodesDir)/clientSocket.o $(socketCodesDir)/socketException.o $(socketCodesDir)/socket.o
	g++ $(LnkOpt) $(mainFilesDir)/clientMain.o $(socketCodesDir)/clientSocket.o $(socketCodesDir)/socketException.o $(socketCodesDir)/socket.o -o clientMain.out

$(mainFilesDir)/serverMain.o: $(mainFilesDir)/serverMain.cpp $(socketHeadersDir)/serverSocket.h $(socketHeadersDir)/socketException.h $(socketHeadersDir)/socket.h
	g++ $(cmpOpt) -o $(mainFilesDir)/serverMain.o $(mainFilesDir)/serverMain.cpp

$(mainFilesDir)/clientMain.o: $(mainFilesDir)/clientMain.cpp $(socketHeadersDir)/clientSocket.h $(socketHeadersDir)/socketException.h $(socketHeadersDir)/socket.h
	g++ $(cmpOpt) -o $(mainFilesDir)/clientMain.o $(mainFilesDir)/clientMain.cpp

$(socketCodesDir)/socket.o: $(socketCodesDir)/socket.cpp $(socketHeadersDir)/socket.h
	g++ $(cmpOpt) -o $(socketCodesDir)/socket.o $(socketCodesDir)/socket.cpp

$(socketCodesDir)/socketException.o: $(socketCodesDir)/socketException.cpp $(socketHeadersDir)/socketException.h
	g++ $(cmpOpt) -o $(socketCodesDir)/socketException.o $(socketCodesDir)/socketException.cpp

$(socketCodesDir)/serverSocket.o: $(socketCodesDir)/serverSocket.cpp $(socketHeadersDir)/serverSocket.h $(socketHeadersDir)/socketException.h $(socketHeadersDir)/socket.h
	g++ $(cmpOpt) -o $(socketCodesDir)/serverSocket.o $(socketCodesDir)/serverSocket.cpp

$(socketCodesDir)/clientSocket.o: $(socketCodesDir)/clientSocket.cpp $(socketHeadersDir)/clientSocket.h $(socketHeadersDir)/socketException.h $(socketHeadersDir)/socket.h
	g++ $(cmpOpt) -o $(socketCodesDir)/clientSocket.o $(socketCodesDir)/clientSocket.cpp

clean:
	find . -name '*.o' -delete && find . -name '*.out' -delete
