#include "move.h"
#include "analyze.h"
#include "extern.h"

//ここからblueの動作を書く
void escape_RDmove(int agentNo) {
	std::vector<std::pair<int, int>> able_moves;

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	able_moves.clear();

	for (int i = 0; i < 4; i++) {
		int nx = blue[agentNo].x + dx[i];
		int ny = blue[agentNo].y + dy[i];

		// マップの範囲内かつ衝突しない位置を列挙
		if (insideMAP(nx, ny) && !agentEX(nx, ny)) {
			able_moves.emplace_back(dx[i], dy[i]);
		}
	}

	if (!able_moves.empty()) {
		std::pair<int, int> selected_move = able_moves[rand() % able_moves.size()];
		blue[agentNo].x += selected_move.first;
		blue[agentNo].y += selected_move.second;
	}

}

void Nearest_move(int agentNo) {
	// 最も近い自陣以外のマスへ向かう
	std::pair<int, int> target = findNearestNonAllySquare(blue[agentNo].x, blue[agentNo].y);
	// ターゲットに向かうための移動を決定する
	if (blue[agentNo].x < target.first &&
		!agentEX(blue[agentNo].x + 1, blue[agentNo].y)) {
		blue[agentNo].x++; // ターゲットが右にある場合、右に移動
	}
	else if (blue[agentNo].x > target.first &&
		!agentEX(blue[agentNo].x - 1, blue[agentNo].y)) {
		blue[agentNo].x--; // ターゲットが左にある場合、左に移動
	}
	else if (blue[agentNo].y < target.second &&
		!agentEX(blue[agentNo].x, blue[agentNo].y + 1)) {
		blue[agentNo].y++; // ターゲットが下にある場合、下に移動
	}
	else if (blue[agentNo].y > target.second &&
		!agentEX(blue[agentNo].x, blue[agentNo].y - 1)) {
		blue[agentNo].y--; // ターゲットが上にある場合、上に移動
	}
	else {
		escape_RDmove(agentNo);
	}
}

void move_b0(void)
{
	analize_pt();

	std::vector<std::pair<int, int>> best_moves;
	double best_pt = -1.0;

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	int trytimes = 3; //試行回数は3回まで
	int depth = 3;

	do {
		best_pt = -1.0; // ポイントをリセット
		best_moves.clear(); // 移動リストをクリア
		srand((unsigned int)time(NULL));

		if (trytimes != 3) {
			depth = (rand() % 3) + 3;
		}

		trytimes--;
		for (int i = 0; i < 4; i++) {
			int nx = blue[0].x + dx[i];
			int ny = blue[0].y + dy[i];

			// マップの範囲内かつ衝突しない位置のみを検証
			if (insideMAP(nx, ny) && !agentEX(nx, ny)) {
				double pt = point(nx, ny, depth, (i == 3 ? 0 : rand() % 2));
				if (pt > best_pt) {
					best_moves.clear();
					best_pt = pt;
					best_moves.emplace_back(dx[i], dy[i]);
				}
				else if (pt == best_pt) {
					best_moves.emplace_back(dx[i], dy[i]);
				}
			}
		}
	} while (best_moves.empty() && trytimes > 0);


	// ランダムに最適な移動先を選択
	if (!best_moves.empty()) {
		std::pair<int, int> selected_move = best_moves[rand() % best_moves.size()];
		blue[0].x += selected_move.first;
		blue[0].y += selected_move.second;
	}
	else {
		Nearest_move(0);
	}
//	printf("2.%d,%d,%d,%d\n", blue[0].x, blue[0].y, blue[1].x, blue[1].y); //check
}

void move_b1(void)
{
	std::vector<std::pair<int, int>> best_moves;
	double best_pt = -1.0;

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };
	int trytimes = 5; //試行回数は5回まで
	int depth = 3;

	do {
		best_pt = -1.0; // ポイントをリセット
		best_moves.clear(); // 移動リストをクリア
		srand((unsigned int)time(NULL));
		if (trytimes != 5) {
			depth = (rand() % 3) + 3;
		}

		trytimes--;
		for (int i = 0; i < 4; i++) {
			int nx = blue[1].x + dx[i];
			int ny = blue[1].y + dy[i];

			// マップの範囲内かつ衝突しない位置のみを検証
			if (insideMAP(nx, ny) && !agentEX(nx, ny)) {
				double pt = point(nx, ny, depth, (rand() % 2));
				if (pt > best_pt) {
					best_moves.clear();
					best_pt = pt;
					best_moves.emplace_back(dx[i], dy[i]);
				}
				else if (pt == best_pt) {
					best_moves.emplace_back(dx[i], dy[i]);
				}
			}
		}
	} while (best_moves.empty() && trytimes > 0);


	// ランダムに最適な移動先を選択
	if (!best_moves.empty()) {
		srand((unsigned int)time(NULL));
		std::pair<int, int> selected_move = best_moves[rand() % best_moves.size()];
		blue[1].x += selected_move.first;
		blue[1].y += selected_move.second;
	}
	else {
		Nearest_move(1);
	}

//	printf("2.%d,%d,%d,%d\n", blue[0].x, blue[0].y, blue[1].x, blue[1].y); //check
}