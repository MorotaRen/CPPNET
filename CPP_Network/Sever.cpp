#include "Sever.h"

bool SeverMaster::SetUp_Windock() {
	//winsock�̏�����
	if (_WINSOCK2API_::WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		std::cout << "�X�^�[�g�A�b�v�Ɏ��s" << std::endl;
		return false;
	}
	//�\�P�b�g�̍쐬
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET) {
		std::cout << "�\�P�b�g�̍쐬�Ɏ��s�F" << WSAGetLastError() << std::endl;
		return false;
	}
	//�\�P�b�g�ݒ�
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SEVERPORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	setsockopt(sock0,
		SOL_SOCKET, SO_REUSEADDR, (const char *)true, sizeof(true));
	return true;
}
int SeverMaster::Sever_main() {
	if (!SetUp_Windock()) {
		std::cout << "�Z�b�g�A�b�v�Ɏ��s���܂����B�I�����܂�" << std::endl;
		return 0;
	}
	std::cout << "�Z�b�g�A�b�v�ɐ���" << std::endl;
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		std::cout << "�o�C���h�Ɏ��s�F" <<WSAGetLastError()<< std::endl;
		return 1;
	}
	if (listen(sock0, 5) != 0) {
		std::cout << "�ڑ��ҋ@�Ɏ��s�F" << WSAGetLastError() << std::endl;
		return 1;
	}

	while (1) {
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock == INVALID_SOCKET) {
			std::cout << "accept���s�F" << WSAGetLastError() << std::endl;
			break;
		}
		errorNum = send(sock, "HELLO", 5, 0);
		if (errorNum < 1) {
			std::cout << "���M���s�F" << WSAGetLastError() << std::endl;
			break;
		}

		closesocket(sock);
	}

	WSACleanup();

	return 0;
}