#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1111;
int n;
int tx, ty;
int dist[N][N];
int _gcd[N][N];

int gcd(int a, int b) {
	if (!a || !b) return 1;
	return a % b == 0 ? b : gcd(b, a % b);
}

int bfs(int sx, int sy) {
	for (int i = 0; i <= n; i++) memset(dist[i], -1, sizeof(dist[i]));
	queue<int> que;
	que.push(sx);
	que.push(sy);
	dist[sx][sy] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		int nx, ny, d;
		if (x == tx && y == ty) return dist[x][y];
		if (x == n || y == n) continue;
		nx = x, ny = y + 1;
        if (nx > ny) swap(nx, ny);
        d = _gcd[nx][ny];
		nx /= d, ny /= d;
		if (dist[nx][ny] == -1) {
			dist[nx][ny] = dist[x][y] + 1;
			que.push(nx), que.push(ny);
		}
		nx = x + 1, ny = y;
        if (nx > ny) swap(nx, ny);
        d = _gcd[nx][ny];
		nx /= d, ny /= d;
		if (dist[nx][ny] == -1) {
			dist[nx][ny] = dist[x][y] + 1;
			que.push(nx), que.push(ny);
		}
	}
	return -1;
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            _gcd[i][j] = gcd(i, j);
	while (~scanf("%d", &n)) {
		scanf("%d%d", &tx, &ty);
        if (tx > ty) swap(tx, ty);
		int ans = bfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}

