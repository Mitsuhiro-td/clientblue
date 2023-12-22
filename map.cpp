#include"extern.h"

unsigned char map[MAX_X][MAX_Y];	//map[x���W][y���W]�Bx���W�͉������By���W�͏c����
struct position blue[2];	//blue
struct position red[2];		//red
struct position old_blue[2];
struct position old_red[2];


void init(void) {
	//�����ʒu
	blue[0].x = 0; blue[0].y = 1;
	blue[1].x = 1; blue[1].y = 0;
	red[0].x = 19; red[0].y = 18;
	red[1].x = 18; red[1].y = 19;

	old_blue[0].x = 0; old_blue[0].y = 1;
	old_blue[1].x = 1; old_blue[1].y = 0;

	//map�̏�����
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			map[i][j] = NONE;
		}
	}

	map[0][1] = BLUE0;
	map[1][0] = BLUE1;
	map[19][18] = red0;
	map[18][19] = red1;
}


//���[�J����blue[]��red[]�����ł́C�Փ˂Ȃǂ̏�񂪂킩��Ȃ��B
//server�����map[][]�����ׂĂ̊�{�f�[�^�ɂȂ�B
//���̂��߁Cmap[][]����blue[]��red[]�̃f�[�^�𔲂��o���K�p������B
void get_agent_xy(void) {
	for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[i][j] == BLUE0) { blue[0].x = i; blue[0].y = j; }
			if (map[i][j] == BLUE1) { blue[1].x = i; blue[1].y = j; }
			if (map[i][j] == red0) { red[0].x = i; red[0].y = j; }
			if (map[i][j] == red1) { red[1].x = i; red[1].y = j; }
		}
	}
}