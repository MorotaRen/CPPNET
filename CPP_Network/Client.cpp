#include "Client.h"
#pragma warning(disable  : 4996)
bool ClientMaster::StartUp_Client() {
	// winsock2�̏�����
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// �\�P�b�g�̍쐬
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// �ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;
	server.sin_port = htons(SEVERPORT);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	return 1;
}
int ClientMaster::Client_main() {
	if (!StartUp_Client()) {
		std::cout << "�Z�b�g�A�b�v�Ɏ��s���܂����B�I�����܂��B" << std::endl;
		return 0;
	}
	// �T�[�o�ɐڑ�
	connect(sock, (struct sockaddr *)&server, sizeof(server));
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n != -1) {
			std::cout <<buf << std::endl;
		}
	}
	// �T�[�o����f�[�^����M
	// winsock2�̏I������
	WSACleanup();

	return 0;
}