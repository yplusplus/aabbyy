#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int inf = 1 << 25;
const int N = 2222;
const int M = 888888;
int g[N], c[N], d[N];
int eh[N], tot, alloc;
int dist[N], cur[N];
int n, m;

struct Edge {
	int u, v, cap, flow, id, next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow, int id) {
	Edge e = {u, v, cap, flow, id, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap, int id) {
	add(u, v, cap, 0, id), add(v, u, 0, 0, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	memset(dist, -1, sizeof(dist));
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (dist[v] == -1 && et[i].cap > et[i].flow) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (dist[v] == dist[u] + 1 && et[i].cap > et[i].flow) {
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
		flow += dfs(s, t, 1 << 30);
	}
	return flow;
}

struct EE {
	int u, v, l, r, id;
	EE(int u, int v, int l, int r, int id) : u(u), v(v), l(l), r(r), id(id) {}
};
vector<EE> edge;

int in[N], out[N];
int cc[44444];

bool check(int mid) {
	init();
	int s = n + m;
	int t = s + 1;
	int ss = t + 1;
	int tt = ss + 1;
	edge.push_back(EE(t, s, mid, inf, 0));
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	for (int i = 0; i < edge.size(); i++) {
		out[edge[i].u] += edge[i].l;
		in[edge[i].v] += edge[i].l;
		addedge(edge[i].u, edge[i].v, edge[i].r - edge[i].l, edge[i].id);
	}
	int cnt = n + m + 2;
	int sum = 0;
	for (int i = 0; i < cnt; i++) {
		if (in[i] == out[i]) continue;
		if (in[i] > out[i]) {
			sum += in[i] - out[i];
			addedge(ss, i, in[i] - out[i], 0);
		} else {
			addedge(i, tt, out[i] - in[i], 0);
		}
	}
	edge.pop_back();
	int ret = Dinic(ss, tt);
	return ret == sum;
}

void solve() {
	int L = 0, R = d[n];
	int ans = -1;
	while (L <= R) {
		int mid = L + R >> 1;
		if (check(mid)) ans = mid, L = mid + 1;
		else R = mid - 1;
	}
	printf("%d\n", ans);
	if (ans == -1) return;
	check(ans);
	for (int i = 0; i < tot; i++) {
		if (et[i].id) {
			cc[et[i].id] += et[i].flow;
		}
	}
	for (int i = 1; i <= alloc; i++) {
		printf("%d\n", cc[i]);
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		alloc = 0;
		for (int i = 0; i < m; i++) scanf("%d", &g[i]);
		d[n] = 0;
		edge.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &c[i], &d[i]);
			d[n] += d[i];
			edge.push_back(EE(n + m, i, 0, d[i], 0));
			for (int j = 0; j < c[i]; j++) {
				int gid, l, r;
				scanf("%d%d%d", &gid, &l, &r);
				alloc++;
				edge.push_back(EE(i, gid + n, l, r, alloc));
				cc[alloc] = l;
			}
		}
		for (int i = 0; i < m; i++) {
			edge.push_back(EE(i + n, n + m + 1, g[i], inf, 0));
		}
		solve();
		puts("");
	}
	return 0;
}
