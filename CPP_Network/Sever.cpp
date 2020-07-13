#include "Sever.h"

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
		if (sock == INVALID_SOCKET) {
			std::cout << "accept失敗：" << WSAGetLastError() << std::endl;
			break;
		}
		errorNum = send(sock, "HELLO", 5, 0);
		if (errorNum < 1) {
			std::cout << "送信失敗：" << WSAGetLastError() << std::endl;
			break;
		}

		closesocket(sock);
	}

	WSACleanup();

	return 0;
}