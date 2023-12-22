#include <stdio.h>
#include "SOC.h"
#include "move.h"
#include "extern.h"

//大域変数
char inbuf[ELEMENT] = { 0 }; // 受信データ
char outbuf[ELEMENT] = { 0 }; // 送信データ
int _temp = 0;	//WAITとCLSで利用。
int turn = 0;		//ターン数
int berr_flag = FALSE;	//反則判定フラグ
int rerr_flag = FALSE;	//反則判定フラグ

void receve(int receve_number, SOCKET sock)
{
	char inbuf[ELEMENT] = { 0 }; // 受信データ
	char temp[ELEMENT] = { 0 };
	char* p;
	char* q = NULL;
	int retry_count = 0;

	int ret = recv(sock, inbuf, sizeof(inbuf), 0);
//	printf("0.受信>%d, %s\n", ret, inbuf); //check
	if (ret <= 0) {
		if (receve_number == 1) { printf("blue先攻，受信1回目が受信エラーで強制終了します。\n"); }
		else if (receve_number == 2) { printf("blue先攻，受信2回目が受信エラーで強制終了します。\n"); }
		else if (receve_number == 3) { printf("red先攻，受信3回目が受信エラーで強制終了します。\n"); }
		else if (receve_number == 4) { printf("red先攻，受信4回目が受信エラーで強制終了します。\n"); }
		else {}
		exit(EXIT_FAILURE);
	}

	strcpy_s(temp, ELEMENT, inbuf);

	p = strtok_s(temp, ",", &q);	//1つ目のトークン表示
	map[0][0] = (unsigned char)atoi(p);
	//	printf("2.map[0][0]>%d\n", map[0][0]); //check

	int flag = 0;
	for (int j = 0; j < MAX_Y; j++) {
		if (flag == 0) {//始めの1回目だけmap[1][0]から始める。
			for (int i = 1; i < MAX_X; i++) {
				p = strtok_s(NULL, ",", &q); //2回目以降は第一引数はNULL
				map[i][j] = (unsigned char)atoi(p);
				//				printf("map[%d][%d]>%d\n", i, j, map[i][j]); //check
			}
			flag++;
		}
		else {
			for (int i = 0; i < MAX_X; i++) {
				p = strtok_s(NULL, ",", &q); //2回目以降は第一引数はNULL
				map[i][j] = (unsigned char)atoi(p);
				//				printf("map[%d][%d]>%d\n", i, j, map[i][j]); //check
			}
		}
	}

	get_agent_xy();
}

void move_blue(SOCKET sock)
{
	char temp[ELEMENT] = { 0 };

	for (int i = 0; i < 2; i++) {
		old_red[i] = red[i];
		old_blue[i] = blue[i];
	}

	move_b0();
	move_b1();

	anti_foul();

	// 送信する座標。
	sprintf_s(outbuf, ELEMENT, "%d,%d,%d,%d", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
	send(sock, outbuf, (int)strlen(outbuf), 0);
	//	printf("送信>%s\n", outbuf); //check
}

int main(void)
{
	printf("ここはclientblueです。\n");
	WSADATA wsaData; // Winsock の初期化。Windows Sockets仕様に関する情報を格納する構造体
		int iRet = WSAStartup(MAKEWORD(2, 0), &wsaData); //Windows Sockets仕様に関する情報を格納する構造体
	if (iRet) {
		// エラー処理.
		_tprintf(_T("Error!(iRet = %d.)\n"), iRet);	// 戻り値を出力.
		WSACleanup();	// WSACleanupで終了処理.
		return -1;	// -1を返して異常終了.
	}

	SOCKET sock;

	int retry_count = 0;
	int connected = 0;
	
	// blueはredに対して待ち時間が発生する恐れがあるため，connectエラー時に再試行する
	while (retry_count < MAX_RETRY && !connected) {
		//AF_INETはIPv4プロトコル。SOCK_STREAMはTCPプロトコル
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET) {
			printf("ソケットの作成に失敗しました。\n");
			WSACleanup();
			return 1;
		}

		//AF_INETはIPv4プロトコル。SOCK_STREAMはTCPプロトコル
		struct sockaddr_in server {};		// アドレスの構造体
		server.sin_family = AF_INET;	// IPv4を指定
		server.sin_port = htons(PORT_BLUE);	// 自分の学籍番号

		InetPton(AF_INET, _T(SERVER_IP), &server.sin_addr.S_un.S_addr);

		if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			// 接続失敗
			int errCode = WSAGetLastError();
			printf("接続に失敗しました。エラーコード: %d\n", errCode);
			perror("connection failed");
			printf("再試行 %d / %d\n\n", retry_count + 1, MAX_RETRY);
			closesocket(sock);
			retry_count++;
			Sleep(RETRY_INTERVAL); // Windowsの場合
		}
		else {
			printf("サーバーに接続しました。\n");
			connected = 1;
		}
	}

	if (!connected) {
		printf("サーバーへの接続を確立できませんでした。\n");
		WSACleanup();
		return 1;
	}

	// 接続成功
	printf("サーバーに接続しました。\n");
	init();

	for (turn = 0; turn < MAX_TURN && berr_flag == FALSE && rerr_flag == FALSE; turn++) {
		if (turn % 2 == 0) {
			printf("Blue先攻。ここから現在のターン数：%d\n", turn);
			move_blue(sock);//blue先攻，送信1回目
			receve(1, sock);	//blue先攻，受信1回目
			printf("上図，Blueの移動結果,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);

			receve(2, sock);	//blue先攻，受信2回目
			printf("上図，redの移動結果,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);
			printf("ここまで現在のターン数：%d\n", turn);
		}
		else {
			printf("red先攻。ここから現在のターン数：%d\n", turn);
			receve(3, sock);	//red先攻，受信3回目
			printf("上図，redの移動結果,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);

			move_blue(sock);//red先攻，送信2回目
			receve(4, sock);	//red先攻，受信4回目
			printf("上図，Blueの移動結果,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);
			printf("ここまで現在のターン数：%d\n", turn);
		}
	}

	shutdown(sock, SD_BOTH); //ソケットを切断。受信、送信を無効にする
	closesocket(sock); // 接続解除。
	WSACleanup(); //WinSockを終了させるAPI関数

	return 0;
}