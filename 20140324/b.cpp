#include <bits/stdc++.h>
using namespace std;

const int N = 211111;
const int M = 111111;
struct Edge {
	int u, v, w;
	void read() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator<(const Edge &x) const {
		return w < x.w;
	}
} edge[M];

int cnt[N];
int n, m;
int dp[N];
int w[N];
int id[N];

struct UFS {
	int fa[N];
	void clear() { for (int i = 0; i <= n; i++) fa[i] = i; }
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	bool Union(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		fa[a] = b;
		return true;
	}
} ufs;

int alloc;
int fa[N];
int pre[N];

int dfs(int u) {
	if (dp[u] != -1) return dp[u];
	if (pre[u] == -1) return dp[u] = 0;
	else return dp[u] = dfs(pre[u]) + w[u];
}

int find(int x) {
	return fa[x] == -1 ? x : fa[x] = find(fa[x]);
}

void solve() {
	ufs.clear();
	alloc = n;
	for (int i = 1; i <= 2 * n; i++) { id[i] = i; }
	for (int i = 1; i <= 2 * n; i++) {
		fa[i] = -1;
		pre[i] = -1;
		if (i <= n) cnt[i] = 1;
		else cnt[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int a = edge[i].u, b = edge[i].v, c = edge[i].w;
		if (ufs.Union(a, b)) {
			alloc++;
			int ra = find(id[a]);
			int rb = find(id[b]);
			fa[ra] = alloc;
			fa[rb] = alloc;
			w[ra] = cnt[rb] * c;
			w[rb] = cnt[ra] * c;
			pre[ra] = pre[rb] = alloc;
			cnt[alloc] = cnt[ra] + cnt[rb];
			id[ra] = id[rb] = alloc;
		}
	}
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		printf("%d\n", dfs(i));
	}
}

int main() {
	freopen("road.in", "r", stdin);
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) { edge[i].read(); }
		sort(edge, edge + m);
		printf("Case %d:\n", Case++);
		solve();
	}
	return 0;
}
