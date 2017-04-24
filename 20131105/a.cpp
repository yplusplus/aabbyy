#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 333;
const int INF = 0x77777777;
int mat[N][N], s[N][N], mx[N][N];

int main() {
	//freopen("in", "r", stdin);
	int n, m, h, w;
	while (~scanf("%d%d%d%d", &n, &m, &h, &w)) {
		memset(s, 0, sizeof(s));
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) mx[i][j] = -INF;
		for (int i = 1 + h; i <= n + h; i++) {
			for (int j = 1 + w; j <= m + w; j++) {
				scanf("%d", mat[i] + j);
			}
		}
		n += h * 2;
		m += w * 2;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
			s[i][j] = mat[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
		for (int r = w; r <= m; r++) {
			int l = r - w + 1;
			for (int u = 1; u <= n; u++) {
				for (int d = u; d <= n; d++) {
					mx[d - u + 1][w] = max(s[d][r] + s[u - 1][l - 1] - s[u - 1][r] - s[d][l - 1], mx[d - u + 1][w]);
				}
			}
		}
		for (int d = h; d <= n; d++) {
			int u = d - h + 1;
			for (int l = 1; l <= m; l++) {
				for (int r = l; r <= m; r++) {
					mx[h][r - l + 1] = max(s[d][r] + s[u - 1][l - 1] - s[u - 1][r] - s[d][l - 1], mx[h][r - l + 1]);
				}
			}
		}
		int ans = mx[h][w];
		for (int i = 1; i < h; i++) ans = max(mx[i][w] + mx[h - i][w], ans);
		for (int i = 1; i < w; i++) ans = max(mx[h][i] + mx[h][w - i], ans);
		printf("%d\n", ans);
	}
	return 0;
}
