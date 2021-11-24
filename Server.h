#pragma once

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <tchar.h>
#include "Comms.h"
using namespace std;
class Server : Comms
{
private:
	SOCKET S_socket, a_socket;
	sockaddr_in service;

public:

	Server()
	{
		this->port = 55555;
	};
	~Server() {};

	int ConnectServer();
	int sendMessage();

};
