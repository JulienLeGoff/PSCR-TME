#include "TCPServer.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace pr {
	void TCPServer::handleClient(Socket scan){
		int lu;
		read(scan.getFD(), &lu, sizeof(int));
		lu++;
		write(scan.getFD(), &lu, sizeof(int));
		scan.close();
	}

	bool TCPServer::startServer(int port){
		ss = new ServerSocket(port);
		if(ss->isOpen()){
			while(1){
				std::cout << "en attente sur le port " << port <<std::endl;
				Socket sc = ss->accept();
				if(sc.isOpen()){
					//handleClient(sc);
					threads.emplace_back(&TCPServer::handleClient, this, sc);
				}
			}
			return true;
		}
		return false;
	}

	TCPServer::~TCPServer(){
		for(auto &t : threads){
			t.join();
		}
	}

	void TCPServer::stopServer(){
		ss->close();
	}
}

