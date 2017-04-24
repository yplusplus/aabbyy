#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

#define MP make_pair
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
const int N = 555;
char maz[N][N];
int n, m;

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

bool iswall(char ch) {
	return ch == '#';
}

pair<int, int> fall[N][N][4];
int dist[N][N][4];

int bfs(int sx, int sy, int tx, int ty) {
	queue<int> que;
	que.push(sx); que.push(sy); que.push(0);
	memset(dist, -1, sizeof(dist));
	dist[sx][sy][0] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		int z = que.front(); que.pop();
		if (x == tx && y == ty) return dist[x][y][z];
		//step
		for (int i = -1; i <= 1; i += 2) {
			int k = (i + z + 4) % 4;
			int nx = x + dx[k], ny = y + dy[k];
			if (!check(nx, ny) || iswall(maz[nx][ny])) continue;
			pair<int, int> pos = fall[nx][ny][z];
			nx = pos.first, ny = pos.second;
			if (dist[nx][ny][z] != -1) continue;
			dist[nx][ny][z] = dist[x][y][z] + 1;
			que.push(nx); que.push(ny); que.push(z);
		}
		//rotate
		for (int i = -1; i <= 1; i += 2) {
			int dir = (z + i + 4) % 4;
			int nx = fall[x][y][dir].first;
			int ny = fall[x][y][dir].second;
			if (dist[nx][ny][dir] != -1) continue;
			dist[nx][ny][dir] = dist[x][y][z] + 1;
			que.push(nx); que.push(ny); que.push(dir);
		}
	}
	return -1;
}

void solve() {
	int sx, sy, tx, ty;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (maz[i][j] == '|') sx = i, sy = j;
			if (maz[i][j] == 'E') tx = i, ty = j;
		}
	}
	memset(fall, -1, sizeof(fall));
	for (int i = 0; i < 4; i++) {
		fall[tx][ty][i] = MP(tx, ty);
	}
	//0
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			if (iswall(maz[i][j])) continue;
			if (iswall(maz[i + 1][j])) fall[i][j][0] = MP(i, j);
			else fall[i][j][0] = fall[i + 1][j][0];
		}
	}
	//1
	for (int j = m - 2; j >= 0; j--) {
		for (int i = 0; i < n; i++) {
			if (iswall(maz[i][j])) continue;
			if (iswall(maz[i][j + 1])) fall[i][j][1] = MP(i, j);
			else fall[i][j][1] = fall[i][j + 1][1];
		}
	}
	//2
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (iswall(maz[i][j])) continue;
			if (iswall(maz[i - 1][j])) fall[i][j][2] = MP(i, j);
			else fall[i][j][2] = fall[i - 1][j][2];
		}
	}
	//3
	for (int j = 1; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (iswall(maz[i][j])) continue;
			if (iswall(maz[i][j - 1])) fall[i][j][3] = MP(i, j);
			else fall[i][j][3] = fall[i][j - 1][3];
		}
	}
	//cout << 123123 << endl;
	int ans = bfs(sx, sy, tx, ty);
	if (ans == -1) puts("Can not escape!");
	else cout << ans << endl;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		//cout << n << " " << m << endl;
		gets(maz[0]);
		for (int i = 0; i < n; i++) { gets(maz[i]); }
		//for (int i = 0; i < n; i++) { cout << maz[i] << endl; }
		//cout << 123 << endl;
		solve();
	}
	return 0;
}
