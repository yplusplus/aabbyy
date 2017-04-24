#include <bits/stdc++.h>
using namespace std;

const int N = 3333;
const int M = N * N;
int dist[N], cur[N];
int eh[N], tot;
int n, m;
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
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front(); que.pop();
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
	for (int i = eh[u]; ~i; i = et[i].next) {
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
		//cout << 123 << endl;
		memcpy(cur, eh, sizeof(eh));
		flow += dfs(s, t, 1 << 30);
	}
	return flow;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		int s = 0, t = 2222;
		for (int i = n + 1; i < t; i++) {
			addedge(i, t, m);
		}
		for (int i = 1; i <= n; i++) {
			addedge(s, i, 2);
			int ti, si;
			scanf("%d%d", &ti, &si);
			for (int j = ti; j < ti + si; j++) {
				addedge(i, j + n + 1, 1);
			}
		}
		int ret = Dinic(s, t);
		if (ret < 2 * n) {
			puts("No");
		} else {
			puts("Yes");
			int a[10];
			for (int i = 1; i <= n; i++) {
				int tot = 0;
				for (int j = eh[i]; ~j; j = et[j].next) {
					int v = et[j].v;
					if (v >= n + 1 && et[j].cap == et[j].flow) {
						a[tot++] = v - n - 1;
					}
				}
				printf("%d %d\n", min(a[0], a[1]), max(a[0], a[1]));
			}
		}
	}
	return 0;
}

