#include <bits/stdc++.h>
using namespace std;

const int N = 555;
int a[N];
int sum[N][N];
int dp[N];
int f[N][N];
int mi[N][N];
int n;
vector<int> vec[N];

int dfs(int l, int r) {
	if (l == r) return 0;
	if (f[l][r] != -1) return f[l][r];
	int res = INT_MAX;
	for (int k = l; k < r; k++) {
		int cost = 0;
		int c = mi[l][k];
		cost += sum[c][r] - sum[c][k];
		c = mi[k + 1][r];
		cost += sum[c][k] - sum[c][l - 1];
		cost += dfs(l, k) + dfs(k + 1, r);
		res = min(res, cost);
	}
	return f[l][r] = res;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		mi[i][i] = a[i];
		for (int j = i + 1; j <= n; j++) {
			mi[i][j] = min(mi[i][j - 1], a[j]);
		}
	}
	for (int i = 1; i < N; i++) {
		sum[i][0] = 0;
		for (int j = 1; j <= n; j++) {
			sum[i][j] = sum[i][j - 1] + (a[j] > i);
		}
	}
	memset(f, -1, sizeof(f));
	vector<int> bag;
	for (int i = 0; i < N; i++) vec[i].clear();
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			bag.resize(j - i + 1);
			for (int k = i; k <= j; k++) {
				bag[k - i] = a[k];
			}
			sort(bag.begin(), bag.end());
			bag.erase(unique(bag.begin(), bag.end()), bag.end());
			if (bag.size() == j - i + 1 && bag[0] == 1 && bag[j - i] == j - i + 1) {
				vec[i - 1].push_back(j);
				//cout << i << " " << j << " " << dfs(i, j) << endl;
			}
		}
	}
	for (int i = 0; i < N; i++) dp[i] = INT_MAX;
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		if (dp[i] == INT_MAX) continue;
		for (int j = 0; j < vec[i].size(); j++) {
			dp[vec[i][j]] = min(dp[vec[i][j]], dp[i] + dfs(i + 1, vec[i][j]));
		}
	}
	if (dp[n] == INT_MAX) puts("impossible");
	else printf("%d\n", dp[n]);
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		solve();
	}
	return 0;
}
