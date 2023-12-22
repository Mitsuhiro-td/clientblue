#ifndef EXTERN_H
#define EXTERN_H

	#include"map.h"


	#ifndef FALSE
	#define FALSE               0
	#endif

	#ifndef TRUE
	#define TRUE                1
	#endif

	// main.cpp
	extern int turn;		//ターン数
	extern int berr_flag;	//反則判定フラグ
	extern int rerr_flag;	//反則判定フラグ

	// map.cpp
	extern unsigned char map[MAX_X][MAX_Y];	//map[x座標][y座標]。x座標は横方向。y座標は縦方向
	extern struct position blue[2];	//blue
	extern struct position red[2];		//red
	extern struct position old_blue[2];
	extern struct position old_red[2];
#endif