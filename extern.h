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
	extern int turn;		//�^�[����
	extern int berr_flag;	//��������t���O
	extern int rerr_flag;	//��������t���O

	// map.cpp
	extern unsigned char map[MAX_X][MAX_Y];	//map[x���W][y���W]�Bx���W�͉������By���W�͏c����
	extern struct position blue[2];	//blue
	extern struct position red[2];		//red
	extern struct position old_blue[2];
	extern struct position old_red[2];
#endif