#include <bits/stdc++.h>
using namespace std;

const int N = 222;
const int M = 222222;
const int inf = 1 << 25;
int eh[N], tot;
int cur[N], dist[N];
int n, m;
int in[N], out[N];

struct Edge {
	int u, v, cap, flow, next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	//cout << u << " -> " << v << " " << cap << endl;
	add(u, v, cap, 0);
	add(v, u, 0, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	memset(dist, -1, sizeof(dist));
	dist[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		//cout << u << endl;
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] == -1) {
				//cout << u << "->" << v << endl;
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	//cout << dist[t] << endl;
	return dist[t] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
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
		//cout << "123123" << endl;
		memcpy(cur, eh, sizeof(cur));
		flow += dfs(s, t, inf);
	}
	return flow;
}

bool pos[N], neg[N];

int main() {
	int first = true;
	int T;
	scanf("%d", &T);
	while (T--) {
		if (!first) puts("");
		else first = false;
		scanf("%d%d", &n, &m);
		int s = 0, t = n * 2 + 1;
		init();
		for (int i = 1; i <= n; i++) { scanf("%d", &in[i]); }
		for (int i = 1; i <= n; i++) { scanf("%d", &out[i]); }
		for (int i = 1; i <= n; i++) {
			addedge(s, i, out[i]);
			addedge(i + n, t, in[i]);
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, v + n, inf);
		}
		int ans = Dinic(s, t);
		cout << ans << endl;
		memset(pos, 0, sizeof(pos));
		memset(neg, 0, sizeof(neg));
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (dist[i] == -1) {
				neg[i] = true;
				cnt++;
			}
			if (dist[i + n] != -1) {
				pos[i] = true;
				cnt++;
			}
		}
		cout << cnt << endl;
		for (int i = 1; i <= n; i++) {
			if (neg[i]) {
				printf("%d -\n", i);
			}
			if (pos[i]) {
				printf("%d +\n", i);
			}
		}
	}
	return 0;
}
