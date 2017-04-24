#include <bits/stdc++.h>
using namespace std;

int n;
void convert(const int &x, const int &y, const int &z, const int &kind, int &i, int &j, int &k) {
	switch (kind) {
		case 0: i = n - z - 1; j = y; k = n - x - 1; break;
		case 1: i = n - z - 1; j = x; k = y; break;
		case 2: i = n - z - 1; j = n - y - 1; k = x; break;
		case 3: i = n - z - 1; j = n - x - 1; k = n - y - 1; break;
		case 4: i = x; j = y; k = n - z - 1; break;
		case 5: i = n - x - 1; j = y; k = z; break;
		default: i = j = k = -1;
	}
}

void rev_convert(const int &x, const int &y, const int &z, const int &kind, int &i, int &j, int &k) {
	switch (kind) {
		case 0: i = n - z - 1; j = y; k = n - x - 1; break;
		case 1: i = y; j = z; k = n - x - 1; break;
		case 2: i = z; j = n - y - 1; k = n - x - 1; break;
		case 3: i = n - y - 1; j = n - z - 1; k = n - x - 1; break;
		case 4: i = x; j = y; k = n - z - 1; break;
		case 5: i = n - x - 1; j = y; k = z; break;
	}
}

const int N = 6;
const int M = 1 << 4;
char mat[N][M][M];
bool vis[M][M][M];
int depth[N][M][M];

int cal() {
	memset(vis, 0, sizeof vis);
	memset(depth, 0, sizeof depth);
	while (1) {
		bool ok = 1;
		for (int x = 0; x < n; ++x) {
			for (int y = 0; y < n; ++y) {
				for (int z = 0; z < n; ++z) {
					if (vis[x][y][z]) continue;
					int i, j, k;
					bool del = 0;
					char ch = 0;
					for (int p = 0; p < N && !del; ++p) {
						convert(x, y, z, p, i, j, k);
						if ('.' == mat[p][i][j]) del = 1, depth[p][i][j] = n;
						if (depth[p][i][j] != k) continue;
						if (ch) {
							if (ch != mat[p][i][j]) del = 1;
						} else ch = mat[p][i][j];
					}
					if (del) vis[x][y][z] = 1, ok = 0;
				}
			}
		}
		for (int p = 0; p < N; ++p) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					int x, y, z;
					while (depth[p][i][j] < n) {
						rev_convert(i, j, depth[p][i][j], p, x, y, z);
						if (vis[x][y][z]) ++depth[p][i][j];
						else break;
					}
				}
			}
		}
		if (ok) break;
	}
	int cnt = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) cnt += vis[i][j][k];
	return n * n * n - cnt;
}

int run() {
	while (cin >> n && n) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < N; ++j) cin >> mat[j][i];
		cout << "Maximum weight: " << cal() << " gram(s)" << endl;;
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
