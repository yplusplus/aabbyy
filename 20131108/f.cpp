#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 111;
int n, m;
int floor[N][N][N];
int dp[N][N][N];
bool visit[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int upx[] = {-1, -1, 0, 0};
int upy[] = {-1, 0, -1, 0};
struct Road {
	int a, b, c;
	int d, e, f;
	int t;
	void read() {
		scanf("%d%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f, &t);
	}
};
vector<Road> tunnel[N];

bool check(int x, int y, int now) {
	int d = n + 1 - now;
	return x >= 1 && x <= d && y >= 1 && y <= d;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	dp[1][1][1] = floor[1][1][1];
	for (int now = 1; now <= n; now++) {
		int r = n + 1 - now, c = n + 1 - now;
		queue<int> que;
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (dp[now][i][j] != -1) {
					que.push(i);
					que.push(j);
				}
			}
		}
		int x, y;
		while (!que.empty()) {
			x = que.front(); que.pop();
			y = que.front(); que.pop();
			visit[x][y] = false;
			//tunnel
			for (int i = 0; i < tunnel[now].size(); i++) {
				if (tunnel[now][i].b != x || tunnel[now][i].c != y) continue;
				int d = tunnel[now][i].d;
				int e = tunnel[now][i].e;
				int f = tunnel[now][i].f;
				int t = tunnel[now][i].t;
				if (dp[d][e][f] == -1 || dp[d][e][f] > dp[now][x][y] + t + floor[d][e][f]) {
					dp[d][e][f] = dp[now][x][y] + t + floor[d][e][f];
				}
			}
			//now
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (!check(nx, ny, now)) continue;
				if (dp[now][nx][ny] == -1 || dp[now][nx][ny] > dp[now][x][y] + floor[now][nx][ny]) {
					dp[now][nx][ny] = dp[now][x][y] + floor[now][nx][ny];
					if (!visit[nx][ny]) {
						visit[nx][ny] = true;
						que.push(nx);
						que.push(ny);
					}
				}
			}
			//now + 1
			if(now + 1 <= n) {
				for (int i = 0; i < 4; i++) {
					int nx = x + upx[i], ny = y + upy[i];
					if (!check(nx, ny, now + 1)) continue;
					if (dp[now + 1][nx][ny] == -1 || dp[now + 1][nx][ny] > dp[now][x][y] + floor[now + 1][nx][ny]) {
						dp[now + 1][nx][ny] = dp[now][x][y] + floor[now + 1][nx][ny];
					}
				}
			}
		}
	}
	printf("%d\n", dp[n][1][1]);
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			int r = n - i + 1, c = n - i + 1;
			for (int j = 1; j <= r; j++) {
				for (int k = 1; k <= c; k++) {
					scanf("%d", &floor[i][j][k]);
				}
			}
		}
		for (int i = 1; i <= n; i++) tunnel[i].clear();
		for (int i = 0; i < m; i++) {
			Road road;
			road.read();
			tunnel[road.a].push_back(road);
		}
		solve();
	}
	return 0;
}
