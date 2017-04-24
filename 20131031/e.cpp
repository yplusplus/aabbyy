#include <bits/stdc++.h>
using namespace std;

const int N = 44444;
const int M = 888888;
int eh[N], cur[N], tot;
int score[N];
int dist[N];
int n;
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
		int u = que.front();
		que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
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
		memcpy(cur, eh, sizeof(eh));
		flow += dfs(s, t, 1 << 30);
	}
	return flow;
}

int get_id(int x, int y) {
	return (x - 1) * n + y;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) scanf("%d", &score[i]);
		init();
		int s = 0, t = get_id(n, n) + n + 1;
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				addedge(s, get_id(i, j), 3);
				addedge(get_id(i, j), get_id(n, n) + i, 3);
				addedge(get_id(i, j), get_id(n, n) + j, 3);
				sum += 3;
			}
		}
		for (int i = 1; i <= n; i++) {
			addedge(get_id(n, n) + i, t, score[i]);
		}
		int ret = Dinic(s, t);
		if (ret != sum) {
			puts("INCORRECT");
		} else {
			puts("CORRECT");
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j < i; j++) {
					int a, b;
					int u = get_id(i, j);
					for (int k = eh[u]; ~k; k = et[k].next) {
						if (et[k].v > get_id(n, n)) {
							if (et[k].flow == 3) {
								a = et[k].v - get_id(n, n);
								b = i + j - a; 
								printf("%d > %d\n", a, b);
								break;
							} else if (et[k].flow == 2) {
								a = et[k].v - get_id(n, n);
								b = i + j - a; 
								printf("%d >= %d\n", a, b);
								break;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

