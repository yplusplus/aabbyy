#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 22222;
const int M = N << 1;
struct Edge {
	int u, v, nx;
	Edge() {}
	Edge(int u, int v, int nx) : u(u), v(v), nx(nx) {}
} edge[M];
int eh[N], ec;

void init() {
	memset(eh, -1, sizeof(eh));
	ec = 0;
}

void addedge(int u, int v) {
	edge[ec] = Edge(u, v, eh[u]);
	eh[u] = ec++;
	edge[ec] = Edge(v, u, eh[v]);
	eh[v] = ec++;
}

#define FOR(i, u) for (int i = u; ~i; i = edge[i].nx)
typedef long long LL;
LL ans;
int n, cnt[N];
bool vis[N];

void dfs1(int x) {
	vis[x] = 1;
	cnt[x] = 1;
	FOR(i, eh[x]) {
		Edge &e = edge[i];
		if (vis[e.v]) continue;
		dfs1(e.v);
		cnt[x] += cnt[e.v];
	}
}

LL cal(int x) { return x * (x - 1) >> 1; }

void dfs2(int x, int s) {
	vis[x] = 1;
	LL tmp = cal(n - 1) - cal(s);
	FOR(i, eh[x]) {
		Edge &e = edge[i];
		if (vis[e.v]) continue;
		tmp -= cal(cnt[e.v]);
		dfs2(e.v, n - cnt[e.v]);
	}
	//cout << x << ' ' << ans << endl;
	ans = max(tmp, ans);
}

LL work() {
	memset(vis, 0, sizeof(vis));
	dfs1(1);
	//for (int i = 1; i <= n; i++) cout << cnt[i] << ' '; cout << endl;
	ans = 0;
	memset(vis, 0, sizeof(vis));
	dfs2(1, 0);
	return ans;
}

int main() {
	//freopen("in", "r", stdin);
	int _, x, y;
	scanf("%d", &_);
	for (int cas = 1; cas <= _; cas++) {
		init();
		scanf("%d", &n);
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &x, &y);
			addedge(x, y);
		}
		printf("Case #%d: %lld\n", cas, work());
	}
	return 0;
}

