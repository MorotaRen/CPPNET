#include "Client.h"
#pragma warning(disable  : 4996)
bool ClientMaster::StartUp_Client() {
	// winsock2の初期化
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		std::cout << "Winsockの初期化に失敗しました。" << std::endl;
		return false;
	}

	// ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout << "ソケットの作成に失敗しました。" << std::endl;
		return false;
	}

	// 接続先指定用構造体の準備
	server.sin_family = AF_INET;
	server.sin_port = htons(SEVERPORT);
	std::cout << "ホストネームの設定(ローカルホストの場合[localhost]を入力してください)：";
	std::cin >> hostname;
	server.sin_addr.S_un.S_addr = inet_addr(hostname);
	if (server.sin_addr.S_un.S_addr == 0xffffffff) {
		struct hostent *host;
		host = gethostbyname(hostname);
		addrptr = (unsigned int **)host->h_addr_list;
		if (host == NULL) {
			if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
				std::cout << "HOST Not found：" << hostname << std::endl;
			}
			return false;
		}
		server.sin_addr.S_un.S_addr = *(unsigned int *)host->h_addr_list[0];
	}

	return true;
}
int ClientMaster::Client_main() {
	if (!StartUp_Client()) {
		std::cout << "セットアップに失敗しました。終了します。" << std::endl;
		return 0;
	}
	std::cout << "セットアップに成功しました。" << std::endl;
	// サーバに接続
	while (*addrptr != NULL)
	{
		server.sin_addr.S_un.S_addr = *(*addrptr);
		if (connect(sock,(struct sockaddr *)&server,sizeof(server)) == 0) {
			break;
		}
		addrptr++;
	}
	if (*addrptr == NULL) {
		std::cout << "全ての接続に失敗しました…："<<WSAGetLastError() << std::endl;
	}
	connect(sock, (struct sockaddr *)&server, sizeof(server));
	memset(buf, 0, sizeof(buf));
	int n = recv(sock, buf, sizeof(buf), 0);
	if (n < 0) {
		std::cout << "受信エラー：" << WSAGetLastError() << std::endl;
		return 0;
	}
	std::cout << buf << std::endl;
	// サーバからデータを受信
	// winsock2の終了処理
	int cmd = 0;
	std::cout << "続ける？：";
	std::cin >> cmd;
	if (cmd == 0) {
		WSACleanup();

		return 0;
	}
	else {
		ClientMaster::Client_main();
	}
}