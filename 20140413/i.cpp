#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
typedef unsigned long long ll;

vector<int> vec[N];
ll ans;
ll cnt[N];
int n;

ll calc(ll x) {
	ll a = x, b = x + 1;
	if (a & 1) b >>= 1;
	else a >>= 1;
	return a * b;
}

void dfs(int u, int fa) {
	cnt[u] = 1;
	ll path = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		dfs(v, u);
		path += cnt[u] * cnt[v];
		cnt[u] += cnt[v];
	}
	ans -= calc(path);
	ans -= path * (n - cnt[u]) * cnt[u];
}

void solve() {
	ans = calc(calc(n - 1));
	dfs(1, 0);
	cout << ans << endl;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) { vec[i].clear(); }
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	solve();
	return 0;
}
