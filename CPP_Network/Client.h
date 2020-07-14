#pragma once
#include "config.h"
class ClientMaster
{
public:
	ClientMaster() {};
	~ClientMaster() {};
	int Client_main();
	bool StartUp_Client();
private:
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[32];
	char hostname[256];
	unsigned int **addrptr;
};