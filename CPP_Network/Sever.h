#pragma once
class SeverMaster
{
public:
	SeverMaster() {};
	~SeverMaster() {};

	bool SetUp_Windock();
private:
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	SOCKET sosk;
};