#pragma once
#include "config.h"
class SeverMaster
{
public:
	SeverMaster() {};
	~SeverMaster() {};

	bool SetUp_Windock();
	int Sever_main();
private:
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	SOCKET sock;
	int errorNum;
};