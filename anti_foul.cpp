#include "extern.h"
#include "analyze.h"



int anti_foul(void) {
	int foul_flag[2] = { FALSE };
	int rt_flag = FALSE;

	for (int i = 0; i < 2; i++) {

		//�΂߂ɓ������甽������

		if (blue[i].x - old_blue[i].x == 1 && blue[i].y - old_blue[i].y == 1) { foul_flag[i] = TRUE; }
		else if (blue[i].x - old_blue[i].x == -1 && blue[i].y - old_blue[i].y == 1) { foul_flag[i] = TRUE; }
		else if (blue[i].x - old_blue[i].x == -1 && blue[i].y - old_blue[i].y == -1) { foul_flag[i] = TRUE; }
		else if (blue[i].x - old_blue[i].x == 1 && blue[i].y - old_blue[i].y == -1) { foul_flag[i] = TRUE; }
//		if (red[i].x - old_red[i].x == 1 && red[i].y - old_red[i].y == 1) { foul_flag[i] = TRUE; }
//		else if (red[i].x - old_red[i].x == -1 && red[i].y - old_red[i].y == 1) { foul_flag[i] = TRUE; }
//		else if (red[i].x - old_red[i].x == -1 && red[i].y - old_red[i].y == -1) { foul_flag[i] = TRUE; }
//		else if (red[i].x - old_red[i].x == 1 && red[i].y - old_red[i].y == -1) { foul_flag[i] = TRUE; }

		//1�^�[���œ�����̂�1�܂������B2�܂��ȏ㓮�����甽��

		if (abs(old_blue[i].x - blue[i].x) >= 2) { foul_flag[i] = TRUE; }
		if (abs(old_blue[i].y - blue[i].y) >= 2) { foul_flag[i] = TRUE; }
//		if (abs(old_red[i].x - red[i].x) >= 2) { foul_flag[i] = TRUE; }
//		if (abs(old_red[i].y - red[i].y) >= 2) { foul_flag[i] = TRUE; }
	}

	for (int i = 0; i < 2; i++) {
		if (foul_flag[i]) {
			blue[i] = old_blue[i];
//			red[i] = old_red[i];
			printf("blue[%d]�ňᔽ������\n�ړ����������܂�\n", i); //check
		}
	}
	return rt_flag;
}