#include "Client.h"
#pragma warning(disable  : 4996)

bool ClientMaster::StartUp_Client() {
	// winsock2�̏�����
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		std::cout << "Winsock�̏������Ɏ��s���܂����B" << std::endl;
		return false;
	}

	// �\�P�b�g�̍쐬
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout << "�\�P�b�g�̍쐬�Ɏ��s���܂����B" << std::endl;
		return false;
	}

	// �ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;
	server.sin_port = htons(SEVERPORT);
	std::cout << "�z�X�g�l�[���̐ݒ�(���[�J���z�X�g�̏ꍇ[localhost]����͂��Ă�������)�F";
	std::cin >> hostname;
	server.sin_addr.S_un.S_addr = inet_addr(hostname);
	if (server.sin_addr.S_un.S_addr == 0xffffffff) {
		struct hostent *host;
		host = gethostbyname(hostname);
		addrptr = (unsigned int **)host->h_addr_list;
		if (host == NULL) {
			if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
				std::cout << "HOST Not found�F" << hostname << std::endl;
			}
			return false;
		}
		server.sin_addr.S_un.S_addr = *(unsigned int *)host->h_addr_list[0];
		// �T�[�o�ɐڑ�
		while (*addrptr != NULL)
		{
			server.sin_addr.S_un.S_addr = *(*addrptr);
			if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0) {
				break;
			}
			addrptr++;
		}
		if (*addrptr == NULL) {
			std::cout << "�S�Ă̐ڑ��Ɏ��s���܂����c�F" << WSAGetLastError() << std::endl;
		}

	}
	else {
		if (connect(sock,(struct sockaddr *)&server,sizeof(server)) != 0) {
			std::cout << "�ڑ��Ɏ��s���܂����c�F" << WSAGetLastError() << std::endl;
			return 1;
		}
	}
	return true;
}
int ClientMaster::Client_main() {
	if (!StartUp_Client()) {
		std::cout << "�Z�b�g�A�b�v�Ɏ��s���܂����B�I�����܂��B" << std::endl;
		return 0;
	}
	std::cout << "�Z�b�g�A�b�v�ɐ������܂����B" << std::endl;
	memset(buf, 0, sizeof(buf));
	int n = recv(sock, buf, sizeof(buf), 0);
	if (n < 0) {
		std::cout << "��M�G���[�F" << WSAGetLastError() << std::endl;
		return 0;
	}
	std::cout << buf << std::endl;
	// �T�[�o����f�[�^����M
	// winsock2�̏I������
	char cmd[2048];
	while (true)
	{
		std::cout << "���b�Z�[�W�F";
		std::cin >> cmd;
		if (!strcmp(cmd, "END")) {
			send(sock, LEAVINGTEXT, sizeof(LEAVINGTEXT), 0);
			WSACleanup();
			break;
		}
		else {
			send(sock, cmd, sizeof(cmd), 0);
		}
	}
	return 0;
}