#ifndef MAP_H //二重でincludeされることを防ぐ
#define MAP_H

#define MAX_X 20	//X座標の最大値
#define MAX_Y 20	//Y座標の最大値
#define NONE 0		//地図上の何もないところ
#define BLUE0 10
#define BLUE1 11
#define BLUE_FP 12
#define BLUE_RD 13
#define red0 20
#define red1 21
#define redfp 22
#define RED_RD 23

#define MAX_TURN 100 //最大ターン数

//xy座標を表す構造体
struct position {
	int x;
	int y;
};

// 色ごとに数値をカウントするための構造体
struct color {
	int blue;
	int red;
	int none;
};

// マップの初期化
void init(void);

//ローカルのblue[]やred[]だけでは，衝突などの情報がわからない。
//serverからのmap[][]がすべての基本データになる。
//そのため，map[][]からblue[]とred[]のデータを抜き出す必用がある。
void get_agent_xy(void);

#endif