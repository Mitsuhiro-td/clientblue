#include "analyze.h"
#include "extern.h"

int agentEX(int x, int y) {
	// いなければ	0 FALSE
	// いたら		1 TRUE

	if (map[x][y] != BLUE0 &&
		map[x][y] != BLUE1 &&
		map[x][y] != red0 &&
		map[x][y] != red1 &&

		// 変更中の衝突検知
		((x != red[0].x) || (y != red[0].y)) &&
		((x != red[1].x) || (y != red[1].y)) &&
		((x != blue[0].x) || (y != blue[0].y)) &&
		((x != blue[1].x) || (y != blue[1].y))) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

int insideMAP(int x, int y) {
	// MAP内は	1 TRUE
	// MAP外は	0 FALSE
	if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

double point(int x, int y, int depth, int retry_RD) {

	// マップの範囲外チェック
	if (!insideMAP(x, y)) {
		return 0.0;
	}

	if (depth == 0) {
		return 0.0;
	}

	double pt = 0.0;

	// 現在のマスを評価
	switch (map[x][y]) {
	case NONE:
		pt += 1.0 + none_paint_bonus + retry_RD; // 未塗装のマス
		break;
	case BLUE_FP:
	case BLUE_RD:
		pt -= 0.5;// 既に青で塗られたマス
		break;
	case redfp:
	case RED_RD:
		pt += 1.5 + repaint_bonus; // 敵プレイヤーのマス
		break;
	case BLUE0:
	case BLUE1:
	case red0:
	case red1:
	default:
		break;
	}

	// 敵および味方エージェントとの衝突を避ける
	for (int i = 0; i < 2; i++) {
		if ((abs(red[i].x - x) <= 1 && abs(red[i].y - y) <= 1) ||
			(abs(blue[i].x - x) <= 1 && abs(blue[i].y - y) <= 1)) {
			pt -= 3.0;
		}
	}

	// 次の移動先を再帰的に探索
	// 近隣のマスの評価（上下左右のみ）
	double max_sub_pt = 0.0;
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	for (int i = 0; i < 4; i++) {
		double sub_pt = point(x + dx[i], y + dy[i], depth - 1, retry_RD) * 0.5; // 減衰係数を適用
		if (sub_pt > max_sub_pt) {
			max_sub_pt = sub_pt;
		}
	}

	return pt + max_sub_pt;
}

std::pair<int, int> findNearestNonAllySquare(int startX, int startY) {
	std::queue<std::pair<int, int>> q;
	std::vector<std::vector<bool>> visited(MAX_X, std::vector<bool>(MAX_Y, false));

	// 初期位置をキューに追加
	q.push({ startX, startY });
	visited[startX][startY] = true;

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	while (!q.empty()) {
		std::pair<int, int> current = q.front();
		q.pop();

		int x = current.first;
		int y = current.second;

		// 自陣・敵機以外のマスを見つけた場合
		if (!agentEX(x, y) &&
			map[x][y] != BLUE_FP &&
			map[x][y] != BLUE_RD) {
			return { x, y };
		}

		// 隣接するマスをキューに追加
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (insideMAP(nx, ny) && !visited[nx][ny]) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	// 最も近いマスが見つからない場合は初期位置を返す
	return { startX, startY };
}