#include <bits/stdc++.h>
using namespace std;

const int N = 555;
const int M = 444444;
const int inf = 1 << 30;
int n, m;
struct Circle {
	int x, y, v, r;
	void read() { scanf("%d%d%d%d", &x, &y, &v, &r); }
} circle[N];

struct Point {
	int x, y, v;
	void read() { scanf("%d%d%d", &x, &y, &v); }	   
} point[N];

int eh[N], tot;
int cur[N];
int dist[N];
struct Edge {
	int u, v, cap, flow, next;
	Edge(int u, int v, int cap, int flow, int next) : u(u), v(v), cap(cap), flow(flow), next(next) {}
	Edge() {}
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow) {
	Edge e(u, v, cap, flow, eh[u]);
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
		flow += dfs(s, t, inf);
	}
	return flow;
}

int sq(int x) { return x * x; }
int get_dist(int a, int b, int c, int d) { return sq(a - c) + sq(b - d); }
int goal[N];
bool visit[N];

bool solve() {
	for (int i = 1; i <= n; i++) { 
		goal[i] = circle[i].v;
   	}
	int sum = 0;
	memset(visit, true, sizeof(visit));
	for (int i = 1; i <= m; i++) {
		if (get_dist(point[i].x, point[i].y, circle[1].x, circle[1].y) <= sq(circle[1].r)) {
			goal[1] += point[i].v;
			visit[i] = false;
			continue;
		}
		bool found = false;
		for (int j = 2; j <= n; j++) {
			if (get_dist(point[i].x, point[i].y, circle[j].x, circle[j].y) <= sq(circle[j].r)) {
				found = true;
			}
		}
		if (found) sum += point[i].v;
		else visit[i] = false;
	}
	for (int i = 2; i <= n; i++) {
		if (goal[i] > goal[1]) return false;
	}
	init();
	int s = 0, t = n + m + 1;
	for (int i = 1; i <= m; i++) {
		if (!visit[i]) continue;
		addedge(s, i, point[i].v);
		for (int j = 2; j <= n; j++) {
			if (get_dist(point[i].x, point[i].y, circle[j].x, circle[j].y) <= sq(circle[j].r)) {
				addedge(i, j + m, inf);
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		addedge(i + m, t, goal[1] - goal[i]);
	}
	return Dinic(s, t) == sum;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			circle[i].read();
		}
		for (int i = 1; i <= m; i++) {
			point[i].read();
		}
		if (solve()) puts("Suiting Success");
		else puts("Lonesome Willy");
	}
	return 0;
}
