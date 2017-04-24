#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 222;
const int M = N * N * N;
const int inf = 1 << 28;
int eh[N], tot;
int cur[N];
int dist[N];
int clean[N][N];

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
	queue<int> que;
	memset(dist, -1, sizeof(dist));
	dist[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
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

int dfs(int u, int t, int d) {
	if (t == u) return d;
	int l = d;
	for (int i = cur[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
			int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
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
		memcpy(cur, eh, sizeof(eh));
		flow += dfs(s, t, inf);
	}
	return flow;
}

int n, m;
int a[N], b[N], c[N];
void build() {
	init();
	int s = 2 * n, t = s + 1;
	for (int i = 0; i < n; i++) {
		addedge(s, i, c[i]);
		addedge(i + n, t, c[i]);
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (b[i] + clean[i][j] < a[j]) addedge(i, j + n, inf);
		}
	}
}

int solve() {
	int sum = 0;
	for (int i = 0; i < n; i++) sum += c[i];
    build();
    return sum - Dinic(2 * n, 2 * n + 1);
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
			c[i] = (c[i] + m - 1) / m;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &clean[i][j]);
			}
		}
		printf("Case %d: %d\n", Case++, solve());
	}
	return 0;
}
