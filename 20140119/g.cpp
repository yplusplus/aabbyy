#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
int n, m;
vector<pair<int, int> > vec[N];
int s[N], top;
int belong[N], bcc, dfn[N], low[N], Dindex;
int cnt[N];
long long val[N];
bool cut[N * 2];
int visit[N];

struct Edge {
	int a, b;
	long long c;
	void read() { scanf("%d%d%lld", &a, &b, &c); }
} edge[N * 2];

void tarjan_dfs(int u, int fa) {
	dfn[u] = low[u] = ++Dindex;
	visit[u] = 1;
	s[++top] = u;
	int tot = 0;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (visit[v] == 1 && v != fa) low[u] = min(low[u], dfn[v]);
		if (visit[v] == 0) {
			tarjan_dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
			cut[vec[u][i].second] = true;
				bcc++;
				while (1) {
					belong[s[top]] = bcc;
					cnt[bcc]++;
					if (s[top--] == v) break;
				}
			}
		}
	}
	visit[u] = 2;
}

void tarjan() {
	top = bcc = Dindex = 0;
	memset(visit, 0, sizeof(visit));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; i++) {
		if (!visit[i]) tarjan_dfs(i, 0);
		if (top) {
			bcc++;
			while (top) {
				belong[s[top--]] = bcc;
				cnt[bcc]++;
			}
		}
	}
}

vector<pair<int, long long> > g[N];
int all;
void dfs(int u) {
	visit[u] = 1;
	all += cnt[u];
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		if (!visit[v]) dfs(v);
	}
}

int son[N];

void dfs2(int u, int fa) {
	//cout << u << " " << fa << endl;
	son[u] = cnt[u];
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		if (v == fa) continue;
		dfs2(v, u);
		son[u] += son[v];
		int id = g[u][i].second;
		if (cut[id]) {
			edge[id].c *= 1LL * (all - son[v]) * son[v];
			//cout << edge[id].a << " " << edge[id].b << " " << edge[id].c << endl;
		}
	}
}

long long delta[N];
long long mid;

bool dfs3(int u, int fa, long long w) {
	//cout << u << " " << fa << " " << w << endl;
	visit[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		if (fa == v) continue;
		if (dfs3(v, u, g[u][i].second)) return true;
	}
	//if (delta[u] > mid) return true;
	//if (delta[u] && val[u] + delta[u] > mid) return true;
	if (val[u] + delta[u] > mid) return true;
	if (w && val[u] + delta[u] + w > mid) {
		if (fa == 0) return true;
		delta[fa] += w;
	}
	return false;
}

bool check() {
	memset(visit, 0, sizeof(visit));
	memset(delta, 0, sizeof(delta));
	for (int i = 1; i <= n; i++) {
		if (!visit[i]) {
			if (dfs3(i, 0, 0)) return false;
		}
	}
	return true;
}

void solve() {
	memset(cut, false, sizeof(cut));
	tarjan();
	for (int i = 1; i <= n; i++) { g[i].clear(); }
	for (int i = 0; i < m; i++) {
		if (cut[i]) {
			int a = belong[edge[i].a], b = belong[edge[i].b];
			//cout << edge[i].a << " " << edge[i].b << endl;
			g[a].push_back(make_pair(b, i));
			g[b].push_back(make_pair(a, i));
		}
	}	
	memset(visit, 0, sizeof(visit));
	for (int i = 1; i <= bcc; i++) {
		if (!visit[i]) {
			all = 0;
			dfs(i);
			dfs2(i, 0);
		}
	}
	for (int i = 1; i <= n; i++) { g[i].clear(); }
	for (int i = 0; i < m; i++) {
		if (cut[i]) {
			int a = edge[i].a, b = edge[i].b;
			g[a].push_back(make_pair(b, edge[i].c));
			g[b].push_back(make_pair(a, edge[i].c));
		}
	}
	long long L = 0, R = 1LL << 60;
	long long ans = 0;
	while (L <= R) {
		mid = L + R >> 1;
		if (check()) {
			ans = mid;
			R = mid - 1;
		} else L = mid + 1;
	}
	cout << ans << endl;
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &val[i]);
			vec[i].clear();
		}
		for (int i = 0; i < m; i++) {
			edge[i].read();
			int a = edge[i].a, b = edge[i].b;
			vec[a].push_back(make_pair(b, i));
			vec[b].push_back(make_pair(a, i));
		}
		printf("Case %d: ", Case++);
		solve();
	}
	return 0;
}

