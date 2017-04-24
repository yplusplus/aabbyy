#include <bits/stdc++.h>
using namespace std;

const int N = 111;
const int M = 1 << 16;
map<int, bool> dp[N][N];
int sum[M], bits[M];
int a[20];
int n, m, k;

bool dfs(int x, int y, int mask) {
	//cout << x << " " << y << " " << mask << endl;
	if (bits[mask] == 1) return true;
	if (dp[x][y].count(mask)) return dp[x][y][mask];
	for (int s = (mask - 1) & mask; s; s = (s - 1) & mask) {
		int t = sum[s];
		if (t % x == 0) {
			bool ret = dfs(x, t / x, s) && dfs(x, y - t / x, mask ^ s);
			if (ret) {
	//cout << x << " " << y << " " << mask << endl;
				return dp[x][y][mask] = true;
			}
		}
		if (t % y == 0) {
			bool ret = dfs(t / y, y, s) && dfs(x - t / y, y, mask ^ s);
			if (ret) {
	//cout << x << " " << y << " " << mask << endl;
				return dp[x][y][mask] = true;
			}
		}
	}
	return dp[x][y][mask] = false;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j].clear();
		}
	}
	for (int mask = 0; mask < (1 << k); mask++) {
		sum[mask] = 0;
		for (int i = 0; i < k; i++) {
			if (mask >> i & 1) {
				sum[mask] += a[i];
			}
		}
	}
	int all = (1 << k) - 1;
	if (sum[all] != n * m || !dfs(n, m, all)) puts("No");
	else puts("Yes");
}

int main() {
	bits[0] = 0;
	for (int i = 1; i < M; i++) {
		bits[i] = bits[i >> 1] + (i & 1);
	}
	int Case = 1;
	while (~scanf("%d", &k), k) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < k; i++) {
			scanf("%d", &a[i]);
		}
		printf("Case %d: ", Case++);
		solve();
	}
	return 0;
}
