// CPP_Network.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "Sever.h"
#include "Client.h"
int main()
{
	int a;
	std::cout << "起動するモードの選択(1:鯖 2:クライアント)";
	std::cin >> a;
	if (a == 1) {
		std::cout << "サーバーを起動します" << std::endl;
		SeverMaster sm;
		sm.Sever_main();
	}
	else {
		std::cout << "クライアントを起動します" << std::endl;
		ClientMaster cm;
		cm.Client_main();

	}
}
