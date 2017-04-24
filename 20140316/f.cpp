#include <bits/stdc++.h>
using namespace std;

typedef vector<string> VS;
typedef vector<bool> VB;
typedef vector<VB> V2B;
const int n = 10;
const int D = 4;
VS mat;
V2B vis;
const int dx[D] = { -1, 1, -1, 1 };
const int dy[D] = { -1, -1, 1, 1 };
inline bool inmat(int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; }

int dfs(int x, int y, int cur) {
	int nx, ny, best = cur;
	for (int i = 0; i < D; ++i) {
		nx = x + dx[i], ny = y + dy[i];
		if (!inmat(nx, ny)) continue;
		if (vis[nx][ny]) continue;
		if ('B' != mat[nx][ny]) continue;
		vis[nx][ny] = 1;
		nx += dx[i], ny += dy[i];
		if (inmat(nx, ny) && ('.' == mat[nx][ny] || '#' == mat[nx][ny])) best = max(dfs(nx, ny, cur + 1), best);
		nx -= dx[i], ny -= dy[i];
		vis[nx][ny] = 0;
	}
	return best;
}

int work() {
	int ans = 0;
	vis.clear();
	vis.resize(n, VB(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if ('W' == mat[i][j]) {
				mat[i][j] = '.';
				ans = max(dfs(i, j, 0), ans);
				mat[i][j] = 'W';
			}
		}
	}
	return ans;
}

int run() {
	int _;
	cin >> _;
	mat.resize(n);
	while (_--) {
		for (int i = 0; i < n; ++i) cin >> mat[i];
		cout << work() << endl;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return run();
}
