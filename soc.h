#ifndef SOC_H //��d��include����邱�Ƃ�h��
#define SOC_H

	//Winsock���g�p����A�v���P�[�V������Ws2_32.lib ���C�u���� �t�@�C���ƃ����N����K�v������B 
	//#pragma �R�����g�́A Ws2_32.lib �t�@�C�����K�v�ł��邱�Ƃ������J�[�Ɏ����B
	#pragma comment(lib,"ws2_32.lib")

	//�����Őݒ肷��
	//#define SERVER_IP "192.168.0.22"  // ��d���p���i" "�j�͏����Ȃ����ƁB
	#define SERVER_IP "127.0.0.1"  // ��d���p���i" "�j�͏����Ȃ����ƁB
	#define PORT_BLUE 23030 //�w�Дԍ��̉�4��������

	#define ELEMENT 2048

	#define MAX_RETRY 5
	#define RETRY_INTERVAL 200 // �~���b�P��
	#define TIMEOUT_SEC 5000 // �^�C���A�E�g�b��

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <tchar.h>
	
//	anti_foul.cpp
	int anti_foul(void);

#endif