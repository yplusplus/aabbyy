#include <bits/stdc++.h>
using namespace std;

const int N = 22222;
const int M = 111111;
const int inf = INT_MAX;
struct Edge {
	int u, v, w, id;
	Edge() {}
	Edge(int u, int v, int w, int id) : u(u), v(v), w(w), id(id) {}
	void read() { scanf("%d%d%d", &u, &v, &w); }
} edge[M];

int n, m;
int low[N], dfn[N], dist[N], belong[N];
int visit[N];
int Dindex, bcc;
int s[N], top;
bool bridge[M];
vector<Edge> vec[N];
int col[M];

void dij(int s) {
	priority_queue<pair<int, int> > que;
	memset(visit, 0, sizeof(visit));
	for (int i = 1; i <= n; i++) dist[i] = inf;
	dist[s] = 0;
	que.push(pair<int, int>(0, s));
	while (!que.empty()) {
		pair<int, int> t = que.top();
		que.pop();
		int u = t.second;
		if (visit[u]) continue;
		visit[u] = 1;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].v, w = vec[u][i].w;;
			if (!visit[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				que.push(pair<int, int>(-dist[v], v));
			}
		}
	}
}

void spfa(int s) {
	for (int i = 1; i <= n; i++) {
		dist[i] = inf;
		visit[i] = 0;
	}
	dist[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = 0;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].v, w = vec[u][i].w;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!visit[v]) {
					visit[v] = 1;
					que.push(v);
				}
			}
		}
	}
}

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++Dindex;
	visit[u] = 1;
	s[++top] = u;
	bool found = false;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].v;
		if (col[vec[u][i].id] != 3) continue;
		if (visit[v] == 1) {
			if (v != fa) low[u] = min(low[u], dfn[v]);
			else if (!found) {
				found = true;
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (visit[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				bridge[vec[u][i].id] = true;
				bcc++;
				while (1) {
					belong[s[top]] = bcc;
					if (s[top--] == v) break;
				}
			}
		}
	}
	visit[u] = 2;
}

void tarjan() {
	memset(visit, 0, sizeof(visit));
	bcc = Dindex = top = 0;
	for (int i = 1; i <= n; i++) {
		if (!visit[i]) dfs(i, 0);
		if (top) {
			bcc++;
			while (top) {
				belong[s[top--]] = bcc;
			}
		}
	}
}

void dfs1(int u, int flag) {
	visit[u] = 1;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].v;
		if (flag == 0) {
			if (dist[v] - dist[u] == vec[u][i].w) {
				col[vec[u][i].id] |= 1;
				if (!visit[v]) dfs1(v, flag);
			}
		} else {
			if (dist[u] - dist[v] == vec[u][i].w) {
				col[vec[u][i].id] |= 2;
				if (!visit[v]) dfs1(v, flag);
			}
		}
	}
}

int que[M];
void solve() {
	memset(col, 0, sizeof(col));
	memset(bridge, false, sizeof(bridge));
	//for (int i = 1; i <= n; i++) { vec[i].clear(); }
	for (int i = 1; i <= m; i++) {
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		vec[u].push_back(Edge(u, v, w, i));
		vec[v].push_back(Edge(v, u, w, i));
	}
	//spfa(1);
	dij(1);
	memset(visit, 0, sizeof(visit));
	dfs1(1, 0);
	memset(visit, 0, sizeof(visit));
	dfs1(n, 1);
	tarjan();
	vector<int> bid;
	int tail = 0;
	for (int i = 1; i <= m; i++) {
		if (bridge[i]) {
			que[tail++] = i;
		}
	}
	printf("%d\n", tail);
	for (int i = 0; i < tail; i++) {
		printf("%d%c", que[i], i == tail - 1 ? '\n' : ' ');
	}
}

int main() {
	freopen("important.in", "r", stdin);
	freopen("important.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		edge[i].read();
	}
	solve();
	return 0;
}
