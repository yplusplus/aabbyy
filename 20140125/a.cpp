#include <bits/stdc++.h>
using namespace std;

const int N = 6;
int obj[N][N][N], mat[N][N], A, B, C, n, m;
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < m; }
const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };

void flood_fill(int x, int y) {
	queue<int> qx, qy;
	int nx, ny;
	qx.push(x); qy.push(y);
	mat[x][y] = 1;
	while (!qx.empty()) {
		x = qx.front(); qx.pop();
		y = qy.front(); qy.pop();
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i]; ny = y + dy[i];
			if (!inmat(nx, ny)) continue;
			if (mat[nx][ny]) continue;
			qx.push(nx); qy.push(ny);
			mat[nx][ny] = 1;
		}
	}
}

int count_hole() {
	for (int i = 0; i < n; i++) if (mat[i][0] == 0) flood_fill(i, 0);
	for (int i = 0; i < n; i++) if (mat[i][m - 1] == 0) flood_fill(i, m - 1);
	for (int i = 0; i < m; i++) if (mat[0][i] == 0) flood_fill(0, i);
	for (int i = 0; i < m; i++) if (mat[n - 1][i] == 0) flood_fill(n - 1, i);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j]) continue;
			flood_fill(i, j);
			cnt++;
		}
	}
	return cnt;
}

bool checkA() {
	int top = -1, bottom = -1;
	n = B; m = C;
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < B; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[i][j][k];
		int c = count_hole();
		if (c == 1) {
			top = i;
			break;
		}
		if (c >= 2) return 0;
	}
	for (int i = A - 1; i >= 0; i--) {
		for (int j = 0; j < B; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[i][j][k];
		int c = count_hole();
		if (c == 1) {
			bottom = i;
			break;
		}
		if (c >= 2) return 0;
	}
	if (top == -1 || bottom == -1) return 0;
	if (top > 0) {
		for (int i = 0; i < B; i++) for (int j = 0; j < C; j++) {
			mat[i][j] = obj[top - 1][i][j] & obj[top][i][j];
		}
		if (count_hole() == 1) return 0;
	}
	if (bottom < A - 1) {
		for (int i = 0; i < B; i++) for (int j = 0; j < C; j++) {
			mat[i][j] = obj[bottom + 1][i][j] & obj[bottom][i][j];
		}
		if (count_hole() == 1) return 0;
	}
	for (int i = top + 1; i < bottom; i++) {
		for (int j = 0; j < B; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[i][j][k];
		if (count_hole() - 1) return 0;
	}
	return 1;
}

bool checkB() {
	int top = -1, bottom = -1;
	n = A; m = C;
	for (int i = 0; i < B; i++) {
		for (int j = 0; j < A; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[j][i][k];
		int c = count_hole();
		if (c == 1) {
			top = i;
			break;
		}
		if (c >= 2) return 0;
	}
	for (int i = B - 1; i >= 0; i--) {
		for (int j = 0; j < A; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[j][i][k];
		int c = count_hole();
		if (c == 1) {
			bottom = i;
			break;
		}
		if (c >= 2) return 0;
	}
	if (top == -1 || bottom == -1) return 0;
	if (top > 0) {
		for (int i = 0; i < A; i++) for (int j = 0; j < C; j++) {
			mat[i][j] = obj[i][top - 1][j] & obj[i][top][j];
		}
		if (count_hole() == 1) return 0;
	}
	if (bottom < B - 1) {
		for (int i = 0; i < A; i++) for (int j = 0; j < C; j++) {
			mat[i][j] = obj[i][bottom + 1][j] & obj[i][bottom][j];
		}
		if (count_hole() == 1) return 0;
	}
	for (int i = top + 1; i < bottom; i++) {
		for (int j = 0; j < A; j++) for (int k = 0; k < C; k++) mat[j][k] = obj[j][i][k];
		if (count_hole() - 1) return 0;
	}
	return 1;
}

bool checkC() {
	int top = -1, bottom = -1;
	n = A; m = B;
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < A; j++) for (int k = 0; k < B; k++) mat[j][k] = obj[j][k][i];
		int c = count_hole();
		if (c == 1) {
			top = i;
			break;
		}
		if (c >= 2) return 0;
	}
	for (int i = C - 1; i >= 0; i--) {
		for (int j = 0; j < A; j++) for (int k = 0; k < B; k++) mat[j][k] = obj[j][k][i];
		int c = count_hole();
		if (c == 1) {
			bottom = i;
			break;
		}
		if (c >= 2) return 0;
	}
	if (top == -1 || bottom == -1) return 0;
	if (top > 0) {
		for (int i = 0; i < A; i++) for (int j = 0; j < B; j++) {
			mat[i][j] = obj[i][j][top - 1] & obj[i][j][top];
		}
		if (count_hole() == 1) return 0;
	}
	if (bottom < C - 1) {
		for (int i = 0; i < A; i++) for (int j = 0; j < B; j++) {
			mat[i][j] = obj[i][j][bottom + 1] & obj[i][j][bottom];
		}
		if (count_hole() == 1) return 0;
	}
	for (int i = top + 1; i < bottom; i++) {
		for (int j = 0; j < A; j++) for (int k = 0; k < B; k++) mat[j][k] = obj[j][k][i];
		if (count_hole() - 1) return 0;
	}
	return 1;
}


int main() {
	ios::sync_with_stdio(0);
	while (cin >> A >> B >> C) {
		for (int i = 0; i < A; i++) {
			for (int j = 0; j < B; j++) {
				for (int k = 0; k < C; k++) {
					cin >> obj[i][j][k];
				}
			}
		}
		if (checkA() || checkB() || checkC()) cout << "DOUGHNUT" << endl;
		else cout << "APPLE" << endl;
	}
	return 0;
}
