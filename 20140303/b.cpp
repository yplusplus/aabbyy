#include <bits/stdc++.h>
using namespace std;

const int N = 111;
const int M = 222222;
const int inf = 1 << 30;
int a[N], b[N];
double profit[N][N];
int dist[N];
bool visit[N];
int low[N];
int pre[N];
int n, m;
int eh[N], tot;

struct Edge {
	int u, v, cap, flow, next, cost;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow, int cost) {
	Edge e = {u, v, cap, flow, eh[u], cost};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap, int cost) {
	add(u, v, cap, 0, cost);
	add(v, u, 0, 0, -cost);
}

bool spfa(int s, int t) {
	queue<int> que;
	for (int i = s; i <= t; i++) { dist[i] = inf; }
	que.push(s);
	pre[s] = -1;
	dist[s] = 0;
	low[s] = inf;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
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
	return dist[t] < inf;
}

void mcmf(int s, int t, int &anscost) {
	int ansflow = 0;
	anscost = 0;
	while (spfa(s, t)) {
		ansflow += low[t];
		anscost += low[t] * dist[t];
		int x = pre[t];
		while (x != -1) {
			et[x].flow += low[t];
			et[x ^ 1].flow -= low[t];
			x = pre[et[x].u];
		}
	}
}

void solve(int Case) {
	int s = 0, t = n + m + 1;
	int min_ans, max_ans;
	init();
	for (int i = 1; i <= n; i++) { addedge(s, i, a[i], 0); }
	for (int j = 1; j <= m; j++) { addedge(j + n, t, b[j], 0); }
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (profit[i][j] < 0) continue;
			int t = profit[i][j] * 100 + 1e-6;
			addedge(i, j + n, inf, t);
		}
	}
	mcmf(s, t, min_ans);
	init();
	int sum = 0;
	for (int i = 1; i <= n; i++) { sum += a[i]; addedge(s, i, a[i], 0); }
	for (int j = 1; j <= m; j++) { addedge(j + n, t, b[j], 0); }
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (profit[i][j] < 0) continue;
			int t = profit[i][j] * 100 + 1e-6;
			addedge(i, j + n, inf, -t);
		}
	}
	mcmf(s, t, max_ans);
	max_ans = -max_ans;
	printf("Problem %d: %.2f to %.2f\n", Case, min_ans / 100.0, max_ans / 100.0);
}

int main() {
	int Case = 0;
	while (~scanf("%d%d", &n, &m), n && m) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int j = 1; j <= m; j++) scanf("%d", &b[j]);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%lf", &profit[i][j]);
			}
		}
		solve(++Case);
	}
	return 0;
}
