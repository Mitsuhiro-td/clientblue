#include "analyze.h"
#include "extern.h"

int agentEX(int x, int y) {
	// ���Ȃ����	0 FALSE
	// ������		1 TRUE

	if (map[x][y] != BLUE0 &&
		map[x][y] != BLUE1 &&
		map[x][y] != red0 &&
		map[x][y] != red1 &&

		// �ύX���̏Փˌ��m
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
	// MAP����	1 TRUE
	// MAP�O��	0 FALSE
	if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

double point(int x, int y, int depth, int retry_RD) {

	// �}�b�v�͈̔͊O�`�F�b�N
	if (!insideMAP(x, y)) {
		return 0.0;
	}

	if (depth == 0) {
		return 0.0;
	}

	double pt = 0.0;

	// ���݂̃}�X��]��
	switch (map[x][y]) {
	case NONE:
		pt += 1.0 + none_paint_bonus + retry_RD; // ���h���̃}�X
		break;
	case BLUE_FP:
	case BLUE_RD:
		pt -= 0.5;// ���ɐœh��ꂽ�}�X
		break;
	case redfp:
	case RED_RD:
		pt += 1.5 + repaint_bonus; // �G�v���C���[�̃}�X
		break;
	case BLUE0:
	case BLUE1:
	case red0:
	case red1:
	default:
		break;
	}

	// �G����і����G�[�W�F���g�Ƃ̏Փ˂������
	for (int i = 0; i < 2; i++) {
		if ((abs(red[i].x - x) <= 1 && abs(red[i].y - y) <= 1) ||
			(abs(blue[i].x - x) <= 1 && abs(blue[i].y - y) <= 1)) {
			pt -= 3.0;
		}
	}

	// ���̈ړ�����ċA�I�ɒT��
	// �ߗׂ̃}�X�̕]���i�㉺���E�̂݁j
	double max_sub_pt = 0.0;
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	for (int i = 0; i < 4; i++) {
		double sub_pt = point(x + dx[i], y + dy[i], depth - 1, retry_RD) * 0.5; // �����W����K�p
		if (sub_pt > max_sub_pt) {
			max_sub_pt = sub_pt;
		}
	}

	return pt + max_sub_pt;
}

std::pair<int, int> findNearestNonAllySquare(int startX, int startY) {
	std::queue<std::pair<int, int>> q;
	std::vector<std::vector<bool>> visited(MAX_X, std::vector<bool>(MAX_Y, false));

	// �����ʒu���L���[�ɒǉ�
	q.push({ startX, startY });
	visited[startX][startY] = true;

	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	while (!q.empty()) {
		std::pair<int, int> current = q.front();
		q.pop();

		int x = current.first;
		int y = current.second;

		// ���w�E�G�@�ȊO�̃}�X���������ꍇ
		if (!agentEX(x, y) &&
			map[x][y] != BLUE_FP &&
			map[x][y] != BLUE_RD) {
			return { x, y };
		}

		// �אڂ���}�X���L���[�ɒǉ�
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (insideMAP(nx, ny) && !visited[nx][ny]) {
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}

	// �ł��߂��}�X��������Ȃ��ꍇ�͏����ʒu��Ԃ�
	return { startX, startY };
}