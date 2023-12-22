#include "analyze.h"
#include "extern.h"

double none_paint_bonus;
double repaint_bonus;

struct color col = { 0 };

int count_color()
{
	col = { 0 };
		for (int j = 0; j < MAX_Y; j++) {
		for (int i = 0; i < MAX_X; i++) {
			if (map[i][j] == BLUE0) { col.blue++; } // ”wŒiF‚ÍÂ
			if (map[i][j] == BLUE1) { col.blue++; } // ”wŒiF‚ÍÂ
			if (map[i][j] == BLUE_FP) { col.blue++; } // ”wŒiF‚ÍÂ
			if (map[i][j] == BLUE_RD) { col.blue++; } // ”wŒiF‚ÍÂ
			if (map[i][j] == red0) { col.red++; } // ”wŒiF‚ÍÔ
			if (map[i][j] == red1) { col.red++; } // ”wŒiF‚ÍÔ
			if (map[i][j] == redfp) { col.red++; } // ”wŒiF‚ÍÔ
			if (map[i][j] == RED_RD) { col.red++; } // ”wŒiF‚ÍÔ
			if (map[i][j] == NONE) { col.none++; } // ”wŒiF‚ÍÔ
		}
	}
	//printf("1.blue>%d, red>%d\n",col.blue,col.red); //check
	return 0;
}


int analize_pt(void){
	none_paint_bonus = 0.0;
	repaint_bonus = 0.0;

	// MAPã‚Ì“h‚ç‚ê‚Ä‚¢‚È‚¢êŠ‚ª‘½‚¢
	for (int i = 5; i >= 1; i--) {
		if (col.none > 30 * i) {
			none_paint_bonus += 0.5;
		}
	}

	// “h‚è‚ª—L—˜
	for (int i = 8; i >= 3; i--) {
		if (col.red + 40 + 5 * i < col.blue) {
			none_paint_bonus += 0.2;
		}
	}

	// “h‚è‚ª•s—˜
	for (int i = 7; i >= -2; i--) {
		if (col.blue + 4 * i < col.red) {
			repaint_bonus += 0.5;
		}
	}
	return 0;

	// I”Õ‚Í“h‚è‘Ö‚¦‚µ—Dæ
	if (turn >= 75) {
		repaint_bonus += 1.0;
	}
}