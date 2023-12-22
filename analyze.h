#ifndef ANALIZE_H
#define ANALIZE_H

	#include <stdlib.h>
	#include <string.h>
	#include <queue>
	#include <vector>

//	analyzeMAP.cpp
	int agentEX(int x, int y);
	int insideMAP(int x, int y);
	double point(int x, int y, int depth, int retry_RD);
	std::pair<int, int> findNearestNonAllySquare(int startX, int startY);

//	analyzePT.cpp
	extern double none_paint_bonus;
	extern double repaint_bonus;
	int analize_pt(void);

#endif
