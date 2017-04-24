#include <bits/stdc++.h>
using namespace std;

const int N = 111;
int dp[N][N][5];
bool visit[N][N][5];
vector<pair<pair<int, int>, int> > vec[N][N];
int n, m, sx, sy, tx, ty;

int getDir(int x, int y, int nx, int ny) {
	int dx = nx - x;
	int dy = ny - y;
	if (dx == 0) {
		if (dy == 1) return 2;
		return 4;
	} else {
		if (dx == 1) return 3;
		return 1;
	}
}

queue<int> que;
void update(int x, int y, int dir, int cost) {
	if (dp[x][y][dir] > cost) {
		dp[x][y][dir] = cost;
		if (!visit[x][y][dir]) {
			visit[x][y][dir] = true;
			que.push(x);
			que.push(y);
			que.push(dir);
		}
	}
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 5; k++) {
				dp[i][j][k] = INT_MAX;
			}
		}
	}
	que.push(sx);
	que.push(sy);
	que.push(0);
	dp[sx][sy][0] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		int dir = que.front(); que.pop();
		visit[x][y][dir] = false;
		for (int i = 0; i < vec[x][y].size(); i++) {
			int nx = vec[x][y][i].first.first;
			int ny = vec[x][y][i].first.second;
			int w = vec[x][y][i].second;
			int ndir = getDir(x, y, nx, ny);
			if (dir == 0) {
				update(nx, ny, ndir, dp[x][y][dir] + 2 * w);
				update(nx, ny, 0, dp[x][y][dir] + 2 * w);
			} else if (dir == ndir) {
				update(nx, ny, ndir, dp[x][y][dir] + w);
				update(nx, ny, 0, dp[x][y][dir] + 2 * w);
			}
		}
	}
	if (dp[tx][ty][0] == INT_MAX) puts("Impossible");
	else printf("%d\n", dp[tx][ty][0]);
}

int main() {
	int Case = 1;
	while (~scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &tx, &ty)) {
		if (!n && !m) break;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				vec[i][j].clear();
			}
		}
		for (int i = 1; i < (n << 1); i++) {
			int x = (i + 1) / 2;
			int z;
			if (i & 1) {
				for (int j = 1; j < m; j++) {
					scanf("%d", &z);
					if (z == 0) continue;
					vec[x][j].push_back(make_pair(make_pair(x, j + 1), z));
					vec[x][j + 1].push_back(make_pair(make_pair(x, j), z));
				}
			} else {
				for (int j = 1; j <= m; j++) {
					scanf("%d", &z);
					if (z == 0) continue;
					vec[x][j].push_back(make_pair(make_pair(x + 1, j), z));
					vec[x + 1][j].push_back(make_pair(make_pair(x, j), z));
				}
			}
		}
		printf("Case %d: ", Case++);
		solve();
	}
	return 0;
}
