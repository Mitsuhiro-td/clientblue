#include <stdio.h>
#include "SOC.h"
#include "move.h"
#include "extern.h"

//���ϐ�
char inbuf[ELEMENT] = { 0 }; // ��M�f�[�^
char outbuf[ELEMENT] = { 0 }; // ���M�f�[�^
int _temp = 0;	//WAIT��CLS�ŗ��p�B
int turn = 0;		//�^�[����
int berr_flag = FALSE;	//��������t���O
int rerr_flag = FALSE;	//��������t���O

void receve(int receve_number, SOCKET sock)
{
	char inbuf[ELEMENT] = { 0 }; // ��M�f�[�^
	char temp[ELEMENT] = { 0 };
	char* p;
	char* q = NULL;
	int retry_count = 0;

	int ret = recv(sock, inbuf, sizeof(inbuf), 0);
//	printf("0.��M>%d, %s\n", ret, inbuf); //check
	if (ret <= 0) {
		if (receve_number == 1) { printf("blue��U�C��M1��ڂ���M�G���[�ŋ����I�����܂��B\n"); }
		else if (receve_number == 2) { printf("blue��U�C��M2��ڂ���M�G���[�ŋ����I�����܂��B\n"); }
		else if (receve_number == 3) { printf("red��U�C��M3��ڂ���M�G���[�ŋ����I�����܂��B\n"); }
		else if (receve_number == 4) { printf("red��U�C��M4��ڂ���M�G���[�ŋ����I�����܂��B\n"); }
		else {}
		exit(EXIT_FAILURE);
	}

	strcpy_s(temp, ELEMENT, inbuf);

	p = strtok_s(temp, ",", &q);	//1�ڂ̃g�[�N���\��
	map[0][0] = (unsigned char)atoi(p);
	//	printf("2.map[0][0]>%d\n", map[0][0]); //check

	int flag = 0;
	for (int j = 0; j < MAX_Y; j++) {
		if (flag == 0) {//�n�߂�1��ڂ���map[1][0]����n�߂�B
			for (int i = 1; i < MAX_X; i++) {
				p = strtok_s(NULL, ",", &q); //2��ڈȍ~�͑�������NULL
				map[i][j] = (unsigned char)atoi(p);
				//				printf("map[%d][%d]>%d\n", i, j, map[i][j]); //check
			}
			flag++;
		}
		else {
			for (int i = 0; i < MAX_X; i++) {
				p = strtok_s(NULL, ",", &q); //2��ڈȍ~�͑�������NULL
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

	// ���M������W�B
	sprintf_s(outbuf, ELEMENT, "%d,%d,%d,%d", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
	send(sock, outbuf, (int)strlen(outbuf), 0);
	//	printf("���M>%s\n", outbuf); //check
}

int main(void)
{
	printf("������clientblue�ł��B\n");
	WSADATA wsaData; // Winsock �̏������BWindows Sockets�d�l�Ɋւ�������i�[����\����
		int iRet = WSAStartup(MAKEWORD(2, 0), &wsaData); //Windows Sockets�d�l�Ɋւ�������i�[����\����
	if (iRet) {
		// �G���[����.
		_tprintf(_T("Error!(iRet = %d.)\n"), iRet);	// �߂�l���o��.
		WSACleanup();	// WSACleanup�ŏI������.
		return -1;	// -1��Ԃ��Ĉُ�I��.
	}

	SOCKET sock;

	int retry_count = 0;
	int connected = 0;
	
	// blue��red�ɑ΂��đ҂����Ԃ��������鋰�ꂪ���邽�߁Cconnect�G���[���ɍĎ��s����
	while (retry_count < MAX_RETRY && !connected) {
		//AF_INET��IPv4�v���g�R���BSOCK_STREAM��TCP�v���g�R��
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET) {
			printf("�\�P�b�g�̍쐬�Ɏ��s���܂����B\n");
			WSACleanup();
			return 1;
		}

		//AF_INET��IPv4�v���g�R���BSOCK_STREAM��TCP�v���g�R��
		struct sockaddr_in server {};		// �A�h���X�̍\����
		server.sin_family = AF_INET;	// IPv4���w��
		server.sin_port = htons(PORT_BLUE);	// �����̊w�Дԍ�

		InetPton(AF_INET, _T(SERVER_IP), &server.sin_addr.S_un.S_addr);

		if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			// �ڑ����s
			int errCode = WSAGetLastError();
			printf("�ڑ��Ɏ��s���܂����B�G���[�R�[�h: %d\n", errCode);
			perror("connection failed");
			printf("�Ď��s %d / %d\n\n", retry_count + 1, MAX_RETRY);
			closesocket(sock);
			retry_count++;
			Sleep(RETRY_INTERVAL); // Windows�̏ꍇ
		}
		else {
			printf("�T�[�o�[�ɐڑ����܂����B\n");
			connected = 1;
		}
	}

	if (!connected) {
		printf("�T�[�o�[�ւ̐ڑ����m���ł��܂���ł����B\n");
		WSACleanup();
		return 1;
	}

	// �ڑ�����
	printf("�T�[�o�[�ɐڑ����܂����B\n");
	init();

	for (turn = 0; turn < MAX_TURN && berr_flag == FALSE && rerr_flag == FALSE; turn++) {
		if (turn % 2 == 0) {
			printf("Blue��U�B�������猻�݂̃^�[�����F%d\n", turn);
			move_blue(sock);//blue��U�C���M1���
			receve(1, sock);	//blue��U�C��M1���
			printf("��}�CBlue�̈ړ�����,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);

			receve(2, sock);	//blue��U�C��M2���
			printf("��}�Cred�̈ړ�����,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);
			printf("�����܂Ō��݂̃^�[�����F%d\n", turn);
		}
		else {
			printf("red��U�B�������猻�݂̃^�[�����F%d\n", turn);
			receve(3, sock);	//red��U�C��M3���
			printf("��}�Cred�̈ړ�����,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);

			move_blue(sock);//red��U�C���M2���
			receve(4, sock);	//red��U�C��M4���
			printf("��}�CBlue�̈ړ�����,bx0>%d, by0>%d, bx1>%d, by1>%d, ", blue[0].x, blue[0].y, blue[1].x, blue[1].y);
			printf("rx0>%d, ry0>%d, rx1>%d, ry1>%d\n", red[0].x, red[0].y, red[1].x, red[1].y);
			printf("�����܂Ō��݂̃^�[�����F%d\n", turn);
		}
	}

	shutdown(sock, SD_BOTH); //�\�P�b�g��ؒf�B��M�A���M�𖳌��ɂ���
	closesocket(sock); // �ڑ������B
	WSACleanup(); //WinSock���I��������API�֐�

	return 0;
}