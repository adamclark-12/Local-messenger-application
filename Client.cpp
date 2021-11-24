#include "stdafx.h"
#include "Client.h"


int Client::Connect()
{

	C_socket = INVALID_SOCKET;
	try
	{
		C_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	catch (...)
	{
		cout << "Error at socket " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	cout << "Client socket OK" << endl;

	ClientService.sin_family = AF_INET;

	InetPton(AF_INET, _T("127.0.0.1"), &ClientService.sin_addr.s_addr);

	ClientService.sin_port = htons(port);
	try
	{
		connect(C_socket, (SOCKADDR*)&ClientService, sizeof(ClientService));
	}
	catch (...)
	{
		cout << "Client connect failed " << endl;
		WSACleanup();
		return 0;
	}
	cout << "Client Connected" << endl;
	while (!exit)
	{
		cout << "Enter your message or Type QUIT to exit" << endl;
		cin.get(Buffer, 200);

		try
		{
			string str(Buffer);
			if (str == "QUIT")
			{
				exit = true;
			}

			int message;
			message = send(C_socket, Buffer, 200, 0);
		}
		catch (...)
		{
			cout << "Server error " << WSAGetLastError() << endl;
			WSACleanup();
			return 0;
		}

		cout << "Message sent " << endl;
		if (!exit)
		{
			Reconnect();

		}
		cin.ignore();
	}
	cout << "Disconnecting " << endl;
	WSACleanup();
	return 0;
}
int Client::Reconnect()
{
	try {
		listen(C_socket, 2) == SOCKET_ERROR;
	}

	catch (...) {
		cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
	}

	cout << "Listen ok! Waiting on message..." << endl;

	try
	{

		this->reMessage = recv(C_socket, reciveBuffer, 200, 0);
	}
	catch (...)
	{
		cout << "client: error " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	string str(reciveBuffer);

	cout << "Data recived " << endl;
	cout << reciveBuffer << endl;
}