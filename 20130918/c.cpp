#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

const int dx[4] = { 1, 0, -1, 0};
const int dy[4] = { 0, 1, 0, -1};
const int N = 555;

bool mat[N][N][4], vis[N][N][4];

bool check(int n, int m) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			bool ok = 0;
			for (int k = 0; k < 4; k++) if (vis[i][j][k]) ok = 1;
			if (!ok) return 0;
		}
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(0);
	int T, n, m, in, out, x;
	cin >> T;
	while (T--) {
		cin >> n >> m >> in >> out;
		memset(mat, 0, sizeof(mat));
		memset(vis, 0, sizeof(vis));
		for (int i = 1, e = n * 2; i < e; i++) {
			int t = i + 1 >> 1;
			if (i & 1) {
				for (int j = 1; j < m; j++) {
					cin >> x;
					if (!x) mat[t][j][1] = mat[t][j + 1][3] = 1;
				}
			} else {
				for (int j = 1; j <= m; j++) {
					cin >> x;
					if (!x) mat[t][j][0] = mat[t + 1][j][2] = 1;
				}
			}
		}
		int cx = 1, cy = in + 1, d = 0;
		while (cx != n + 1 || cy != out + 1) {
			if (vis[cx][cy][d]) break;
			//cout << cx << ' ' << cy << ' ' << d << endl;
			vis[cx][cy][d] = 1;
			for (int i = -1; i <= 2; i++) {
				if (mat[cx][cy][i + d & 3]) {
					cx += dx[i + d & 3];
					cy += dy[i + d & 3];
					d = i + d & 3;
					break;
				}
			}
			//cout << "nx " << cx << ' ' << cy << ' ' << d << endl;
		}
		if (check(n, m)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}







