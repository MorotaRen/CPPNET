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
		std::cout << "�T�[�o�[���N�����܂�" << std::endl;
		sm.Sever_main();
		break;
	case CLIENT:
		std::cout << "�N���C�A���g���N�����܂�" << std::endl;
		cm.Client_main();
		break;
	default:
		break;
	}
}