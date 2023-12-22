#include"extern.h"

unsigned char map[MAX_X][MAX_Y];	//map[x座標][y座標]。x座標は横方向。y座標は縦方向
struct position blue[2];	//blue
struct position red[2];		//red
struct position old_blue[2];
struct position old_red[2];


void init(void) {
	//初期位置
	blue[0].x = 0; blue[0].y = 1;
	blue[1].x = 1; blue[1].y = 0;
	red[0].x = 19; red[0].y = 18;
	red[1].x = 18; red[1].y = 19;

	old_blue[0].x = 0; old_blue[0].y = 1;
	old_blue[1].x = 1; old_blue[1].y = 0;

	//mapの初期化
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


//ローカルのblue[]やred[]だけでは，衝突などの情報がわからない。
//serverからのmap[][]がすべての基本データになる。
//そのため，map[][]からblue[]とred[]のデータを抜き出す必用がある。
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