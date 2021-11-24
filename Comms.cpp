#include "stdafx.h"
#include "Comms.h"

int Comms::CommsSetUp()
{
	WRequested = MAKEWORD(2, 2);
	try
	{
		wsaerr = WSAStartup(WRequested, &wsaData);
	}
	catch (...)
	{
		cout << "The winsock dll found!" << endl;
		return 0;
	}

	cout << "The status: " << wsaData.szSystemStatus << endl;

}