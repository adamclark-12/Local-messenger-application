#include "stdafx.h"
#include "Server.h"

int Server::ConnectServer()
{

	S_socket = INVALID_SOCKET;
	try
	{
		S_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	catch (...)
	{
		cout << "error at socket " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;

	}

	cout << "Socket is Ok!" << endl;

	try
	{

		service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		bind(S_socket, (SOCKADDR*)&service, sizeof(service));
	}
	catch (...)
	{
		cout << "bind failed: " << WSAGetLastError() << endl;
		closesocket(S_socket);
		WSACleanup();
		return 0;
	}

	cout << "Bind is Ok " << endl;
	try {
		listen(S_socket, 1) == SOCKET_ERROR;
	}
	catch (...)
	{
		cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
	}

	cout << "Listen ok! Waiting on connections..." << endl;


	fromlen = sizeof(socket_type);
	retval = getsockopt(S_socket, SOL_SOCKET, SO_TYPE, (char*)&socket_type, &fromlen);
	fromlen = sizeof(from);
	try
	{
		a_socket = accept(S_socket, (SOCKADDR*)&from, &fromlen);
	}
	catch (...)
	{
		cout << "Accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	try
	{

		retval = getnameinfo((SOCKADDR*)&from, fromlen, hostsr, NI_MAXHOST, servstr, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

	}
	catch (...)
	{
		cout << "getnameinfo failed: " << retval << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accept connection from host " << " and port " << servstr << endl;
	cout << "Accept connection Waiting for message" << endl;

	while (!exit)
	{


		try
		{

			reMessage = recv(a_socket, reciveBuffer, 200, 0);
		}
		catch (...)
		{
			cout << "client: error " << WSAGetLastError() << endl;
			WSACleanup();
			return 0;
		}
		string str(reciveBuffer);
		if (str == "QUIT")
		{
			exit = true;

		}
		cout << "Data recived " << endl;
		cout << reciveBuffer << endl;

		if (!exit)
		{
			sendMessage();
		}

	}
	cout << "User Disconected " << endl;
	WSACleanup();
	return 0;

}
int Server::sendMessage()
{
	try
	{
		connect(a_socket, (SOCKADDR*)&service, sizeof(service));
	}
	catch (...)
	{
		cout << "Client connect failed " << endl;
		WSACleanup();
		return 0;
	}
	cout << "Enter your message... " << endl;
	cin.get(Buffer, 200);

	try
	{

		int message;
		message = send(a_socket, Buffer, 200, 0);
	}
	catch (...)
	{
		printf("Sever send error %ld.\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	cout << "Message sent " << endl;

	cin.ignore();
}