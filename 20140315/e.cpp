#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int N = 17;
int n, m, tot;
int steps[N][N][1 << 14];
char board[N][N];
pii pos[N];
int type[N];
int id[N][N];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int kx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int ky[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int bx[] = {-1, -1, 1, 1};
int by[] = {-1, 1, -1, 1};
int rx[] = {-1, 1, 0, 0};
int ry[] = {0, 0, 1, -1};
//K B R

int get_type(char chess) {
	if (chess == 'K') return 0;
	if (chess == 'B') return 1;
	if (chess == 'R') return 2;
	return -1;
}

bool inmat(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

bool is_safe(int x, int y, int mask) {
	int nx, ny;
	for (int i = 0; i < tot; i++) {
		if (mask >> i & 1) {
			if (type[i] == 0) {
				for (int j = 0; j < 8; j++) {
					nx = pos[i].first + kx[j], ny = pos[i].second + ky[j];
					if (x == nx && y == ny) return false;
				}
			} else if (type[i] == 1) {
				for (int j = 0; j < 4; j++) {
					nx = pos[i].first, ny = pos[i].second;
					while (true) {
						nx += bx[j], ny += by[j];
						if (!inmat(nx, ny)) break;
						if (x == nx && ny == y) return false;
						if (id[nx][ny] != -1 && (mask >> id[nx][ny] & 1)) break;
					}
				}
			} else if (type[i] == 2) {
				for (int j = 0; j < 4; j++) {
					nx = pos[i].first, ny = pos[i].second;
					while (true) {
						nx += rx[j], ny += ry[j];
						if (!inmat(nx, ny)) break;
						if (x == nx && ny == y) return false;
						if (id[nx][ny] != -1 && (mask >> id[nx][ny] & 1)) break;
					}
				}
			} else {
				//
			}
		}
	}
	return true;
}

int solve() {
	int sx, sy;
	tot = 0;
	memset(id, -1, sizeof(id));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//memset(steps, -1, sizeof(steps[i][j]));
			if (board[i][j] == '.') continue;
			if (board[i][j] == '*') sx = i, sy = j;
			else {
				pos[tot] = pii(i, j);
				type[tot] = get_type(board[i][j]);
				assert(type[tot] != -1);
				id[i][j] = tot++;
			}
		}
	}
	int all = (1 << tot) - 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k <= all; k++) {
				steps[i][j][k] = -1;
			}
		}
	}
	queue<int> que;
	que.push(sx);
	que.push(sy);
	que.push(all);
	steps[sx][sy][all] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		int now = que.front(); que.pop();
		//cout << "***************" << endl;
		//cout << x << " " << y << " " << now << endl;
		if (now == 0) return steps[x][y][now];
		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			int next = now;
			//cout << nx << " " << ny << " " << next << endl;
			if (inmat(nx, ny) && is_safe(nx, ny, now)) {
				//cout << id[nx][ny] << endl;
				if (id[nx][ny] != -1 && (now >> id[nx][ny] & 1)) {
					next ^= (1 << id[nx][ny]);
				}
				//cout << nx << " " << ny << " " << next << endl;
				//cout << steps[nx][ny][next] << endl;
				if (steps[nx][ny][next] == -1) {
					//cout << "push" << endl;
					steps[nx][ny][next] = steps[x][y][now] + 1;
					que.push(nx);
					que.push(ny);
					que.push(next);
				}
			}
		}
	}
	return -1;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) { scanf("%s", board[i]); }
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
