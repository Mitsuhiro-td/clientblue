#ifndef SOC_H //二重でincludeされることを防ぐ
#define SOC_H

	//Winsockを使用するアプリケーションはWs2_32.lib ライブラリ ファイルとリンクする必要がある。 
	//#pragma コメントは、 Ws2_32.lib ファイルが必要であることをリンカーに示す。
	#pragma comment(lib,"ws2_32.lib")

	//自分で設定する
	//#define SERVER_IP "192.168.0.22"  // 二重引用符（" "）は消さないこと。
	#define SERVER_IP "127.0.0.1"  // 二重引用符（" "）は消さないこと。
	#define PORT_BLUE 23030 //学籍番号の下4桁を書く

	#define ELEMENT 2048

	#define MAX_RETRY 5
	#define RETRY_INTERVAL 200 // ミリ秒単位
	#define TIMEOUT_SEC 5000 // タイムアウト秒数

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <tchar.h>
	
//	anti_foul.cpp
	int anti_foul(void);

#endif