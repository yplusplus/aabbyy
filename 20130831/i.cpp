#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
#define ll long long
const int N = 55555;
vector<pair<int, int> >vec[N];

ll ans;
ll dp[N];
int n, m;
void dfs(int u, int fa) {
	dp[u] = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		ll w = vec[u][i].second;
		if (fa == v) continue;
		dfs(v, u);
		ans = max(ans, dp[u] + dp[v] + w);
		dp[u] = max(dp[u], dp[v] + w);
	}
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			vec[a].push_back(make_pair(b, c));
			vec[b].push_back(make_pair(a, c));
		}
		ans = -(1LL << 60);
		dfs(1, 0);
		cout << ans << endl;
	}
	return 0;
}

