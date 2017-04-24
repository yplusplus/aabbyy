#include <bits/stdc++.h>
using namespace std;

const int N = 222;
const int M = 555555;
const int inf = 1 << 28;
int n, m;
int eh[N], tot;
int low[N], pre[N];
int dist[N];
int ans, anscost;
bool visit[N];

struct Edge {
	int u, v, cap, cost, flow, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int cost, int flow) {
	Edge e = {u, v, cap, cost, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap, int cost) {
	add(u, v, cap, cost, 0), add(v, u, 0, -cost, 0);
}

bool spfa(int s, int t) {
	memset(visit, false, sizeof(visit));
	queue<int> que;
	for (int i = 0; i < N; i++) dist[i] = -inf;
	pre[s] = -1;
	dist[s] = 0;
	que.push(s);
	low[s] = inf;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] < dist[u] + et[i].cost) {
				dist[v] = dist[u] + et[i].cost;
				pre[v] = i;
				low[v] = min(low[u], et[i].cap - et[i].flow);
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dist[t] > 0;
}

void mcmf(int s, int t) {
	ans = anscost = 0;
	while (spfa(s, t)) {
		ans += low[t];
		anscost += low[t] * dist[t];
		int x = pre[t];
		while (x != -1) {
			et[x].flow += low[t];
			et[x ^ 1].flow -= low[t];
			x = pre[et[x].u];
		}
	}
}

int sale[N];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 2; i <= n; i++) {
			scanf("%d", &sale[i]);
		}
		init();
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			addedge(a, b, c, -d);
			addedge(b, a, c, -d);
		}
		int s = 1, t = n + 1;
		for (int i = 2; i <= n; i++) {
			addedge(i, t, inf, sale[i]);
		}
		mcmf(s, t);
		printf("%d\n", anscost);
	}
	return 0;
}
