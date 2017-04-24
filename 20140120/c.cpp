#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 55;
char maz[N][N];
int color[N][N];
int area1, area2;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int n, m;

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}


void bfs(int c, char id, int &area) {
	queue<int> que;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (color[i][j] == c) {
				que.push(i);
				que.push(j);
			}
		}
	}
	//cout << c << " " << id << " " << area << endl;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (!check(nx, ny)) continue;
			if (color[nx][ny]) continue;
			if (maz[nx][ny] == id) {
				area++;
				color[nx][ny] = c;
				que.push(nx);
				que.push(ny);
			}
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++) { scanf("%s", maz[i]); }
		int k, id;
		int area1 = 1, area2 = 1;
		memset(color, 0, sizeof(color));
		color[n - 1][0] = 1;
		color[0][m - 1] = 2;
		bfs(1, maz[n - 1][0], area1);
		bfs(2, maz[0][m - 1], area2);
		scanf("%d", &k);
		//cout << area1 << " " << area2 << endl;
		for (int i = 0; i < k; i++) {
			scanf("%d", &id);
			if (i & 1) bfs(2, id + '0', area2);
			else bfs(1, id + '0', area1);
		//cout << area1 << " " << area2 << endl;
		}
		cout << area1 << endl;
		cout << area2 << endl;
	}
	return 0;
}
