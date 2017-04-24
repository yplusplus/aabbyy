#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000000LL;
const int N = 111;
vector<int> vec[N];
long long dp[N][2][N];
long long tmp[2][N];
int n;

long long add(long long a, long long b) {
	return (a + b) % MOD;
}

long long mul(long long a, long long b) {
	return a * b % MOD;
}

void dfs(int u, int fa) {
	dp[u][0][0] = 1;
	dp[u][1][0] = 1;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		dfs(v, u);
		memset(tmp, 0, sizeof(tmp));
		for (int j = n; j >= 0; j--) {
			for (int k = 0; k <= j; k++) {
				tmp[0][j] += (dp[u][0][j - k] * dp[v][0][k] + (j - k - 1 >= 0 ? dp[u][0][j - k - 1] * dp[v][1][k] : 0));
				tmp[1][j] += (dp[u][1][j - k] * dp[v][1][k] + (j - k - 1 >= 0 ? dp[u][1][j - k - 1] * dp[v][1][k] : 0) + dp[u][1][j - k] * dp[v][0][k]);
				tmp[0][j] %= MOD;
				tmp[1][j] %= MOD;
			}
		}
		memcpy(dp[u], tmp, sizeof(tmp));
	}
}

int main() {
	freopen("subtrees.in", "r", stdin);
	freopen("subtrees.out", "w", stdout);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	memset(dp, 0, sizeof(dp));
	dfs(1, 0);
	long long ans[N] = {0};
	for (int i = 1; i <= n; i++) {
		cout << add(dp[1][0][i], dp[1][1][i - 1]) << endl;;
	}
	return 0;
}
