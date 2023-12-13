#ifndef SRC_FTPSERVER_H_
#define SRC_FTPSERVER_H_

#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"
#include <vector>

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class FTPServer {
	char* path;

public :
	FTPServer(char* path): ConnectionHandler(), path(path) {}
	void handleClient(Socket scan);
};

} // ns pr

#endif /* SRC_FTPSERVER_H_ */
