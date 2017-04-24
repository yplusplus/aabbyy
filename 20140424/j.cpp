#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
vector<int> g[N];
vector<int> dag[N];
int belong[N];
int dfn[N], low[N], Dindex, bcc;
int s[N], top;
int n, m;
int visit[N];

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++Dindex;
	visit[u] = 1;
	s[++top] = u;
	bool found = false;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (visit[v] == 1) {
			if (v != fa) low[u] = min(low[u], low[v]);
			else if (!found) { found = true; }
			else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (visit[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				bcc++;
				while (true) {
					belong[s[top]] = bcc;
					if (s[top--] == v) break;
				}
			}
		}
	}
	visit[u] = 2;
}

void tarjan() {
	bcc = top = Dindex = 0;
	memset(visit, 0, sizeof(visit));
	for (int i = 1; i <= n; i++) {
		if (!visit[i]) {
			dfs(i, 0);
			if (top) {
				bcc++;
				while (top) {
					belong[s[top--]] = bcc;
				}
			}
		}
	}
}

int dep[N];

void dfs2(int u, int fa, int d) {
	dep[u] = d;
	visit[u] = 1;
	for (int i = 0; i < dag[u].size(); i++) {
		int v = dag[u][i];
		if (visit[v]) continue;
		dfs2(v, u, d + 1);
	}
}

void solve() {
	tarjan();
	for (int u = 1; u <= n; u++) {
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (belong[v] != belong[u]) {
				dag[belong[u]].push_back(belong[v]);
			}
		}
	}
	//for (int i = 1; i <= n; i++) { cout << i << " " << belong[i] << endl; }
	if (bcc == 1) {
		cout << 1 << " " << 1 << endl;
		return;
	}
	int idx1 = 1, idx2 = 1;
	memset(visit, 0, sizeof(visit));
	dfs2(1, 0, 1);
	for (int i = 1; i <= bcc; i++) {
		if (dep[idx1] < dep[i]) idx1 = i;
	}
	//cout << idx1 << endl;
	memset(visit, 0, sizeof(visit));
	dfs2(idx1, 0, 1);
	for (int i = 1; i <= bcc; i++) {
		if (dep[idx2] < dep[i]) idx2 = i;
	}
	//cout << idx2 << endl;
	for (int i = 1; i <= n; i++) {
		if (belong[i] == idx1) {
			idx1 = i;
			break;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (belong[i] == idx2) {
			idx2 = i;
			break;
		}
	}
	if (idx1 > idx2) swap(idx1, idx2);
	cout << idx1 << " " << idx2 << endl;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	solve();
	return 0;
}
