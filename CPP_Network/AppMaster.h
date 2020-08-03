#pragma once
#include "Sever.h"
#include "Client.h"
#include "config.h"
void Start(int mode) {
	SeverMaster sm;
	ClientMaster cm;
	switch (mode)
	{
	case SERVER:
		std::cout << "サーバーを起動します" << std::endl;
		sm.Sever_main();
		break;
	case CLIENT:
		std::cout << "クライアントを起動します" << std::endl;
		cm.Client_main();
		break;
	default:
		break;
	}
}