#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 1 << 30;
const int N = 55555;
const int M = 333333;
int n, m;
int eh[N], tot;
int dist[N], cur[N];
int cost[5555];
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

int que[N], head, tail;
bool bfs(int s, int t) {
	head = tail = 0;
	for (int i = s; i <= t; i++) dist[i] = -1;
	dist[t] = 0;
	que[tail++] = t;
	while (head < tail && dist[s] == -1) {
		int u = que[head++];
		for (int i = eh[u]; i != -1; i = et[i].next) {
			if (et[i ^ 1].cap > et[i ^ 1].flow && dist[et[i].v] == -1) {
				dist[et[i].v] = dist[u] + 1;
				que[tail++] = et[i].v;
			}
		}
	}
	return dist[s] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; i != -1; i = et[i].next) {
		if (et[i].cap > et[i].flow && dist[u] == dist[et[i].v] + 1) {
			int tmp = dfs(et[i].v, t, min(et[i].cap - et[i].flow, l));
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
		for (int i = s; i <= t; i++) cur[i] = eh[i];
		flow += dfs(s, t, inf);
	}
	return flow;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		int s = 0, t = n + m + 1;
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &cost[i]);
			addedge(i, t, cost[i]);
		}
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			sum += c;
			addedge(s, n + i, c);
			addedge(n + i, a, inf);
			addedge(n + i, b, inf);
		}
		printf("%d\n", sum - Dinic(s, t));
	}
	return 0;
}