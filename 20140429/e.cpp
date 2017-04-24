#include <bits/stdc++.h>
using namespace std;

int MOD;
const int N = 111;
int dp[N][1 << 10];
bool visit[N][1 << 10];
int forbid[15];
int len, n, m;

int dfs(int t, int state) {
	if (t == 0) return dp[t][state] = 1;
	if (visit[t][state]) return dp[t][state];
	visit[t][state] = true;
	int mask = 0;
	for (int i = 0; i < n; i++) {
		if (state >> i & 1) {
			mask |= forbid[i];
		}
	}
	int res = 0;
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < n; j++) {
			if (mask >> j & 1) continue;
			res = (res + dfs(i, state | (1 << j)) * dfs(t - 1 - i, state)) % MOD;
		}
	}
	return dp[t][state] = res;
}

int main() {
	while (cin >> MOD >> len >> n >> m) {
		memset(forbid, 0, sizeof(forbid));
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			//forbid[v] |= 1 << u;
			forbid[u] |= 1 << v;
		}
		memset(visit, 0, sizeof(visit));
		cout << dfs(len / 2, 0) << endl;
	}
	return 0;
}
