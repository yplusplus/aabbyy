#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 111;
int dp[N][N];
int val[N];
int n, k;
vector<int> vec[N];

void dfs(int u, int fa) {
	memset(dp[u], 0, sizeof(dp[u]));
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		dfs(v, u);
		for (int j = k; j >= 0; j--) {
			for (int l = 0; l <= j; l++) {
				dp[u][j] = max(dp[u][j], dp[u][j - l] + dp[v][l]);
			}
		}
	}
	for (int i = k; i >= 1; i--) {
		dp[u][i] = dp[u][i - 1] + val[u];
	}
}

int main() {
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &val[i]);
			vec[i].clear();
		}
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(b);
			vec[b].push_back(a);
		}
		dfs(0, -1);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans = max(ans, dp[i][k]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
