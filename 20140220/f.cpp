#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
int n, m;
vector<pair<int, int> > g[N];
int s[N], tail, tot;
int dfn[N], low[N], Dindex;
bool visit[N], ins[N];
int belong[N];

void dfs(int u, int fa) {
	visit[u] = true;
	ins[u] = true;
	s[tail++] = u;
	dfn[u] = low[u] = ++Dindex;
	int cnt = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first;
		if (v == fa && cnt == 0) {
			cnt++;
			continue;
		}
		if (!visit[v]) dfs(v, u);
		low[u] = min(low[u], low[v]);
		if (low[v] > dfn[u]) {
			//briage
		}
	}
	if (low[u] == dfn[u]) {
		int v;
		do {
			v = s[--tail];
			belong[v] = tot;
			ins[v] = false;
		} while (v != u);
		tot++;
	}
}

void tarjan() {
	tail = Dindex = tot = 0;
	memset(ins, false, sizeof(ins));
	memset(dfn, 0, sizeof(dfn));
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < n; i++) {
		if (!dfn[i]) {
			dfs(i, -1);
			int v;
			for (int i = 0; i < tail; i++) {
				v = s[--tail];
				belong[v] = tot;
				ins[v] = false;
			}
			tot++;
		}
	}
}

vector<pair<int, int> > vec[N];
vector<int> bag;
bool dfs2(int u, int fa) {
	bool res = false;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		bool ret = dfs2(v, u);
		res |= ret;
		if (ret) bag.push_back(vec[u][i].second);
	}
	if (u == belong[n - 1]) res = true;
	return res;
}

void solve() {
	bag.clear();
	for (int i = 0; i < n; i++) vec[i].clear();
	tarjan();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < g[i].size(); j++) {
			int v = g[i][j].first;
			if (belong[i] != belong[v]) {
				vec[belong[i]].push_back(make_pair(belong[v], g[i][j].second));
				//vec[belong[v]].push_back(make_pair(belong[i], g[i][j].second));
			}
		}
	}
	//for (int i = 0; i < n; i++) {
		//cout << i << " " << belong[i] << endl;
	//}
	dfs2(belong[0], -1);
	sort(bag.begin(), bag.end());
	printf("%d\n", (int) bag.size());
	for (int i = 0; i < bag.size(); i++) {
		printf("%d%c", bag[i], i == bag.size() - 1 ? '\n' : ' ');
	}
	if ((int) bag.size() == 0) puts("");
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++) g[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a].push_back(make_pair(b, i));
			g[b].push_back(make_pair(a, i));
		}
		solve();
	}
	return 0;
}
