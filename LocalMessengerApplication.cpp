// LocalMessengerApplication.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "stdafx.h"
#include "Client.h"
#include "Server.h"
#include "Comms.h"
#define client
//#define server
int main()
{
	Client *C = new Client();
	//Server *S = new Server();
#ifdef server
	S->ConnectServer();
#endif
#ifdef client
	C->Connect();

#endif
	system("pause");
}