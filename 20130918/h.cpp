#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int inf = 1 << 30;
const int K = 5555;
const int M = 111111;
int comp[K];
int dist[K];
int eh[K], tot, cur[K];
int n, m, k;
struct Edge {
	int u, v, cap, flow, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs(int s, int t) {
	memset(dist, -1, sizeof(dist));
	queue<int> que;
	que.push(s);
	while (!que.empty() && dist[t] == -1) {
		int u = que.front();
		que.pop();
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int t, int u, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap - et[i].flow && dist[v] == dist[u] + 1) {
			int tmp = dfs(t, v, min(l, et[i].cap - et[i].flow));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

int Dinic(int s, int t) {
	int flow = 0;
	while (bfs(s, t)) {
		for (int i = 0; i <= t; i++) cur[i] = eh[i];
		flow += dfs(s, t, inf);
	}
	return flow;
}

struct EE {
	int u, v, c;
	void read() {
		scanf("%d%d%d", &u, &v, &c);
	}
} ee[3333];

vector<pair<int, int> > vec[1111];

int low[K], pre[K], cnt[K];
int isap(int s, int t, int n) {
	int u, v, now, flow = 0;
	memset(dist, 0, sizeof(dist));
	//memset(low, 0, sizeof(low));
	memset(cnt, 0, sizeof(cnt));
	for (u = 0; u <= n; u++) cur[u] = eh[u];
	low[s] = inf, cnt[0] = n, u = s;
	while (dist[s] < n) {
		for (now = cur[u]; now != -1; now = et[now].next)
			if (et[now].cap - et[now].flow && dist[u] == dist[v = et[now].v] + 1) break;
		if (now != -1) {
			cur[u] = pre[v] = now;
			low[v] = min(et[now].cap - et[now].flow, low[u]);
			u = v;
			if (u == t) {
				for (; u != s; u = et[pre[u]].u) {
					et[pre[u]].flow += low[t];
					et[pre[u] ^ 1].flow -= low[t];
				}
				flow += low[t], low[s] = inf;
			}
		} else {
			if (--cnt[dist[u]] == 0) break;
			dist[u] = n, cur[u] =eh[u];
			for (now = eh[u]; now != -1; now = et[now].next)
			if (et[now].cap - et[now].flow && dist[u] > dist[et[now].v] + 1)
				dist[u] = dist[et[now].v] + 1;
			cnt[dist[u]] ++;
			if (u != s) u = et[pre[u]].u;
		}
	}
	return flow;
}

int main() {
	while (~scanf("%d%d", &n, &k), n + k) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i <= k; i++) {
			scanf("%d", &comp[i]);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int u, v, c, w;
			ee[i].read();
			scanf("%d", &w);
			comp[ee[i].c] -= w;
			vec[ee[i].u].push_back(make_pair(ee[i].v, ee[i].c));
		}
		init();
		int s = 0, t = k + 1;
		int sum = 0;
		for (int i = 1; i <= k; i++) {
			if (comp[i] >= 0) addedge(s, i, comp[i]), sum += comp[i];
			else if (comp[i] < 0) addedge(i, t, -comp[i]);
		}

		for (int i = 0; i < m; i++) {
			int v = ee[i].v;
			for (int j = 0; j < vec[v].size(); j++) {
				if (ee[i].c != vec[v][j].second) {
					addedge(ee[i].c, vec[v][j].second, inf);
				}
			}
		}
		//int ans = sum - Dinic(s, t);
		int ans = sum - isap(s, t, t + 1);
		printf("%d\n", ans);
	}
	return 0;
}

