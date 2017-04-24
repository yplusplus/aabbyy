#include <cstring>
#include <iostream>
#include <climits>
using namespace std;

const int N = 1 << 11;
char matrix[N][N];
int cnt[N][N];
int R, C;

inline int cal(int a, int b, int c, int d) { return cnt[c][d] - cnt[c][b - 1] - cnt[a - 1][d] + cnt[a - 1][b - 1]; }
int run() {
	int n, m, x, y;
	while (~scanf("%d%d%d%d", &n, &m, &x, &y)) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", matrix[i]);
		}
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cnt[i + x + 1][j + y + 1] = matrix[i][j] == 'X';
			}
		}
		R = n + x + 1;
		C = m + y + 1;
		int answer = INT_MAX;
		for (int i = 0; i <= R + x; ++i) {
			for (int j = 1; j <= C + y; ++j) {
				cnt[i][j] += cnt[i][j - 1];
			}
			if (i == 0) continue;
			for (int j = 0; j <= C + y; ++j) {
				cnt[i][j] += cnt[i - 1][j];
			}
		}
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				int c = 0;
				for (int a = i; a < R; a += x) {
					for (int b = j; b < C; b += y) {
						c += (cal(a, b, a + x - 1, b + y - 1) != 0);
					}
				}
				answer = min(c, answer);
			}
		}
		//for (int i = 0; i < n; ++i) { for (int j = 0; j < m; ++j) { cout << cnt[i][j] << ' '; } cout << endl; }
		printf("%d\n", answer);
	}
	return 0;
}

int main() {
	//freopen("in", "r", stdin);
	//ios::sync_with_stdio(0);
	return run();
}
