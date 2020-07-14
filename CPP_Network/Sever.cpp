#include "Sever.h"
#pragma warning(disable : 4996)
bool SeverMaster::SetUp_Windock() {
	//winsockの初期化
	if (_WINSOCK2API_::WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		std::cout << "スタートアップに失敗" << std::endl;
		return false;
	}
	//ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET) {
		std::cout << "ソケットの作成に失敗：" << WSAGetLastError() << std::endl;
		return false;
	}
	//ソケット設定
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SEVERPORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	setsockopt(sock0,
		SOL_SOCKET, SO_REUSEADDR, (const char *)true, sizeof(true));
	return true;
}
int SeverMaster::Sever_main() {
	if (!SetUp_Windock()) {
		std::cout << "セットアップに失敗しました。終了します" << std::endl;
		return 0;
	}
	std::cout << "セットアップに成功" << std::endl;
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		std::cout << "バインドに失敗：" <<WSAGetLastError()<< std::endl;
		return 1;
	}
	if (listen(sock0, 5) != 0) {
		std::cout << "接続待機に失敗：" << WSAGetLastError() << std::endl;
		return 1;
	}

	while (1) {
		len = sizeof(client);
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		std::cout << "接続者：" << inet_ntoa(client.sin_addr) << "接続者PORT：" << ntohs(client.sin_port) << std::endl;
		if (sock == INVALID_SOCKET) {
			std::cout << "accept失敗：" << WSAGetLastError() << std::endl;
			break;
		}
		char WelcomeText[1024] = "接続を確認しました。ようこそ";
		errorNum = send(sock, WelcomeText, sizeof(WelcomeText), 0);
		while (true)
		{
			char recetext[2048];
			errorNum = recv(sock,recetext,sizeof(recetext),0);
			while (recetext[0] != '\0')
			{
				if (!strcmp(recetext, "END")) {
					std::cout << "サーバーを落とします。" << std::endl;
					break;
				}
				else {
					std::cout << "相手：" << recetext << std::endl;
					memset(recetext, '\0', sizeof(recetext));
				}
			}

		}
		if (errorNum < 1) {
			std::cout << "送信失敗：" << WSAGetLastError() << std::endl;
			break;
		}

		closesocket(sock);
		break;
	}

	WSACleanup();

	return 0;
}