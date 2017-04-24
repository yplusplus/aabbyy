#include <bits/stdc++.h>
using namespace std;

const int N = 2505;
int C[N][N];
int dp[15][N << 1];
int MOD;
int n;

void solve() {
	for (int i = 0; i < N; i++) {
		C[i][0] = C[i][i] = 1 % MOD;
		for (int j = 1; j < i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
	memset(dp, 0, sizeof(dp));
	dp[0][n] = 1 % MOD;
	for (int i = 0; i < 15; i++) {
		for (int j = 1; j <= n; j++) {
			if (!dp[i][j]) continue;
			for (int k = 0; k * 3 <= j; k++) {
				int two = j - 3 * k;
				if (two & 1) continue;
				two >>= 1;
				dp[i + 1][two + k] = (dp[i + 1][two + k] + 1LL * C[two + k][k] * dp[i][j]) % MOD;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 15; i++) {
		ans = (ans + dp[i][1]) % MOD;
	}
	cout << ans << endl;
}

int main() {
	freopen("twothree.in", "r", stdin);
	freopen("twothree.out", "w", stdout);
	ios::sync_with_stdio(false);
	while (cin >> n >> MOD) {
		solve();
	}
	return 0;
}
