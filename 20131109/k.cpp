#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 333;
const int M = 888888;
const int inf = 1 << 28;
int st[N], ed[N];
int c[N][N], d[N][N], e[N][N], f[N][N];

struct Edge {
	int u, v, cost, cap, flow, next;
};

struct MinCostMaxFlowSolver {
	Edge et[M];
	int eh[N], tot;
	bool visit[N];
	int dist[N];
	int low[N], pre[N];
	int minCost, maxFlow;
	void init() {
		memset(eh, -1, sizeof(eh));
		tot = 0;
	}
	void add(int u, int v, int cost, int cap, int flow) {
		Edge e = {u, v, cost, cap, flow, eh[u]};
		et[tot] = e;
		eh[u] = tot++;
	}
	void addedge(int u, int v, int cost, int cap) {
		add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
	}
	bool spfa(int s, int t) {
		queue<int> que;
		memset(visit, false, sizeof(visit));
		for (int i = 0; i < N; i++) dist[i] = inf;
		dist[s] = 0;
		que.push(s);
		low[s] = inf;
		pre[s] = -1;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			visit[u] = false;
			for (int i = eh[u]; ~i; i = et[i].next) {
				int v = et[i].v;
				if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
					dist[v] = dist[u] + et[i].cost;
					pre[v] = i;
					low[v] = min(low[u], et[i].cap - et[i].flow);
					if (!visit[v]) {
						que.push(v);
						visit[v] = true;
					}
				}
			}
		}
		return dist[t] != inf;
	}
	void run(int s, int t) {
		minCost = maxFlow = 0;
		while (spfa(s, t)) { 
			int x = pre[t];
			maxFlow += low[t];
			minCost += low[t] * dist[t];
			while (x != -1) {
				et[x].flow += low[t];
				et[x ^ 1].flow -= low[t];
				x = pre[et[x].u];
			}
		}
	}
} mcmf;

int n, m, k;
int main() {
	while (~scanf("%d%d%d", &n, &m, &k), n + m + k) {
		for (int i = 1; i <= n; i++) scanf("%d%d", &st[i], &ed[i]);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &c[i][j]);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &d[i][j]);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &e[i][j]);
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &f[i][j]);
		mcmf.init();
		int s = 0, ss = 2 * n + m + 1, t = ss + 1;
		//cout << s << " " << ss << " " << t << endl;
		mcmf.addedge(s, ss, 0, m);
		for (int i = 1; i <= m; i++) {
			mcmf.addedge(ss, 2 * n + i, 0, 1);
			for (int j = 1; j <= n; j++) {
				if (c[j][i] >= ed[j]) continue;
				int tmp = max(0, c[j][i] - st[j]);
				mcmf.addedge(2 * n + i, j + n, tmp * k + d[j][i], 1);
			}
		}
		for (int i = 1; i <= n; i++) {
			mcmf.addedge(s, i, 0, 1);
			mcmf.addedge(i + n, t, 0, 1);
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (e[i][j] + ed[i] >= ed[j]) continue;
				int tmp = max(0, e[i][j] + ed[i] - st[j]);
				mcmf.addedge(i, j + n, tmp * k + f[i][j], 1);
			}
		}
		mcmf.run(s, t);
		if (mcmf.maxFlow == n) printf("%d\n", mcmf.minCost);
		else puts("-1");
	}
	return 0;
}
