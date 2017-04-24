#include <bits/stdc++.h>
using  namespace std;

const int N = 2222;
int room[N];
pair<int, int> group[N];

int mx[N], my[N];
int dx[N], dy[N], dis;
bool visit[N];
vector<int> vec[N], g[N];
int n;

bool bfs() {
	queue<int> que;
	dis = 1 << 30;
	memset(dx, -1, sizeof(dx));
	memset(dy, -1, sizeof(dy));
	for (int i = 0; i < n; i++) {
		if (mx[i] == -1) {
			que.push(i);
			dx[i] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		if (dx[u] > dis) break;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i];
			if (dy[v] == -1) {
				dy[v] = dx[u] + 1;
				if (my[v] == -1) dis = dy[v];
				else {
					dx[my[v]] = dy[v] + 1;
					que.push(my[v]);
				}
			}
		}
	}
	return dis != 1 << 30;
}

bool dfs(int u) {
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (!visit[v] && dy[v] == dx[u] + 1) {
			visit[v] = true;
			if (my[v] != -1 && dy[v] == dis) continue;
			if (my[v] == -1 || dfs(my[v])) {
				my[v] = u, mx[u] = v;
				return true;
			}
		}
	}
	return false;
}

int dfn[N], low[N], Dindex, belong[N], scc;
int s[N], top;
void tarjan_dfs(int u) {
	int v;
	dfn[u] = low[u] = ++Dindex;
	s[++top] = u, visit[u] = true;
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i];
		if (!dfn[v]) tarjan_dfs(v), low[u] = min(low[u], low[v]);
		else if (visit[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		scc++;
		do {
			v = s[top--];
			visit[v] = false;
			belong[v] = scc;
		} while (v != u);
	}
}

void tarjan() {
	top = scc = Dindex = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < 2 * n; i++) {
		if (!dfn[i]) {
			tarjan_dfs(i);
			if (top) {
				scc++;
				while (top) {
					int v = s[top--];
					belong[v] = scc;
				}
			}
		}
	}
}

int Match() {
	memset(mx, -1, sizeof(mx));
	memset(my, -1, sizeof(my));
	int cnt = 0;
	while (bfs()) {
		memset(visit, false, sizeof(visit));
		for (int i = 0; i < n; i++) {
			//cout << i << endl;
			if (mx[i] == -1 && dfs(i)) cnt++;
		}
	}
	return cnt;
}

bool between(int a, int b, int c) {
	return (b <= a && a <= c);
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) scanf("%d", &room[i]);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &group[i].first, &group[i].second);
		}
		for (int i = 0; i < 2 * n; i++) vec[i].clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (between(room[i], group[j].first, group[j].second)) {
					vec[i].push_back(j);
				}
			}
		}
		//cout << "match begin" << endl;
		int ret = Match();
		//cout << ret << endl;
		//cout << "match ok" << endl;
		if (ret != n) {
			puts("Let's search for another office.");
		} else {
			for (int i = 0; i < 2 * n; i++) g[i].clear();
			for (int i = 0; i < n; i++) {
				//cout << i << " " << mx[i] << endl;
				g[mx[i] + n].push_back(i);
			}
			for (int u = 0; u < n; u++) {
				for (int i = 0; i < vec[u].size(); i++) {
					int v = vec[u][i];
					g[u].push_back(v + n);
				}
			}
			tarjan();
			//cout << "tarjan ok" << endl;
			//cout << scc << endl;
			if (scc < n) {
				cout << "Ask Shiftman for help." << endl;
			} else {
				cout << "Perfect!" << endl;
				for (int i = 0; i < n; i++) {
					cout << my[i] + 1;
					if (i + 1 == n) cout << endl;
					else cout << " ";
				}
			}
		}
	}
	return 0;
}

