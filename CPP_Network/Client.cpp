#include "Client.h"
#pragma warning(disable  : 4996)
bool ClientMaster::StartUp_Client() {
	// winsock2の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	// ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// 接続先指定用構造体の準備
	server.sin_family = AF_INET;
	server.sin_port = htons(SEVERPORT);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	return 1;
}
int ClientMaster::Client_main() {
	if (!StartUp_Client()) {
		std::cout << "セットアップに失敗しました。終了します。" << std::endl;
		return 0;
	}
	// サーバに接続
	connect(sock, (struct sockaddr *)&server, sizeof(server));
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n != -1) {
			std::cout <<buf << std::endl;
		}
	}
	// サーバからデータを受信
	// winsock2の終了処理
	WSACleanup();

	return 0;
}