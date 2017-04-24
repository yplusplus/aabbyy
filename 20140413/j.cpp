#include <bits/stdc++.h>
using namespace std;

const int N = 66;
unsigned long long dp[N][N][N];
int digit[N];

unsigned long long dfs(int i, int target, int sum, int r, bool e) {
	if (i == -1) {
		return sum == target && r == 0;
	}
	if (!e && dp[i][sum][r] != -1) return dp[i][sum][r];
	int u = e ? digit[i] : 1;
	unsigned long long res = 0;
	for (int d = 0; d <= u; d++) {
		res += dfs(i - 1, target, sum + d, (r * 2 + d) % target, e && d == u);
	}
	return e ? res : dp[i][sum][r] = res;
}

unsigned long long calc(unsigned long long x) {
	int tot = 0;
	while (x) {
		digit[tot++] = x & 1;
		x >>= 1;
	}
	unsigned long long res = 0;
	for (int i = 1; i <= tot; i++) {
		memset(dp, -1, sizeof(dp));
		res += dfs(tot - 1, i, 0, 0, 1);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	unsigned long long n;
	while (cin >> n) {
		cout << calc(n) << endl;
	}
	return 0;
}
