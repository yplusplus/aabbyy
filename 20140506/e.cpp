#include <bits/stdc++.h>
using namespace std;

typedef pair<int, long long> pii;
typedef long long ll;
const int N = 2222;
const ll inf = 1LL << 61;
vector<pii> vec[N];
vector<int> dag[N];
int n, m, st;
int dfn[N], low[N], Dindex, belong[N], scc;
bool ins[N];
int s[N], top;
int cnt[N];
ll dist[N];
bool neg[N];
bool reach[N];

void dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u;
	ins[u] = true;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			ins[v] = false;
			belong[v] = scc;
		} while (v != u);
	}
}

void tarjan() {
	scc = top = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(ins, 0, sizeof(ins));
	memset(belong, 0, sizeof(belong));
	for (int i = 1; i <= n; i++) {
		if (!dfn[i] && reach[i]) {
			dfs(i);
			if (top) {
				scc++;
				while (top) { belong[s[top--]] = scc; }
			}
		}
	}
}

bool find_neg_circle(int sid) {
	queue<int> que;
	int scnt = 0, sedge = 0;
	for (int i = 1; i <= n; i++) {
		if (belong[i] == sid) {
			for (int j = 0; j < vec[i].size(); j++) {
				sedge += belong[vec[i][j].first] == sid;
			}
			ins[i] = false;
			dist[i] = 0;
			que.push(i);
			scnt++;
		}
	}
	int que_cnt = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		ins[u] = false;
		que_cnt++;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (belong[v] != sid) continue;
			if (dist[v] > dist[u] + vec[u][i].second) {
				dist[v] = dist[u] + vec[u][i].second;
				if (!ins[v]) {
					ins[v] = true;
					que.push(v);
					cnt[v]++;
					if (cnt[v] >= scnt + 2) {// || que_cnt >= 10 * (scnt + sedge)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void _dfs(int u) {
	reach[u] = true;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (!reach[v]) {
			_dfs(v);
		}
	}
}

void spfa(int s) {
	queue<int> que;
	for (int i = 1; i <= n; i++) dist[i] = inf, ins[i] = false;
	dist[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		ins[u] = false;
		//cout << u << endl;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (neg[belong[v]]) continue;
			if (dist[v] > dist[u] + vec[u][i].second) {
				dist[v] = dist[u] + vec[u][i].second;
				if (!ins[v]) {
					ins[v] = true;
					que.push(v);
				}
			}
		}
	}
}

void __dfs(int u) {
	neg[u] = true;
	for (int i = 0; i < dag[u].size(); i++) {
		int v = dag[u][i];
		if (!neg[v]) {
			__dfs(v);
		}
	}
}

void solve() {
	memset(reach, false, sizeof(reach));
	_dfs(st);
	//for (int i = 1; i <= n; i++) { cout << i << " " << reach[i] << endl; }
	//cout << "_dfs ok" << endl;
	tarjan();
	//cout << scc << endl; for (int i = 1; i <= n; i++) { cout << i << " " << belong[i] << endl; } cout << "tarjan ok" << endl;
	for (int u = 1; u <= n; u++) {
		if (!reach[u]) continue;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (!reach[v]) continue;
			if (belong[u] != belong[v]) {
				dag[belong[u]].push_back(belong[v]);
			}
		}
	}
	memset(neg, false, sizeof(neg));
	for (int i = 1; i <= scc; i++) {
		if (find_neg_circle(i)) {
			if (!neg[i]) __dfs(i);
			//cout << i << " has neg_circle" << endl;
		}
	}
	//cout << "123123123" << endl; for (int i = 1; i <= scc; i++) { cout << i << " " << neg[i] << endl; }
	spfa(st);
	for (int i = 1; i <= n; i++) {
		//cout << i << endl;
		if (!reach[i]) {
			puts("*");
		} else if (neg[belong[i]]) {
			puts("-");
		} else {
			cout << dist[i] << endl;
		}
	}
}

int main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &st);
	for (int i = 1; i <= n; i++) vec[i].clear(), dag[i].clear();
	for (int i = 0; i < m; i++) {
		int u, v;
		long long w;
		cin >> u >> v >> w;
		//scanf("%d%d%d", &u, &v, &w);
		vec[u].push_back(pii(v, w));
	}
	solve();
	return 0;
}
