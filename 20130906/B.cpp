#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 444;
typedef long long LL;
struct Edge {
	int u, v, c, nx;
	Edge() {}
	Edge(int u, int v, int c, int nx) : u(u), v(v), c(c), nx(nx) {}
} edge[N * N * 10];
int eh[N * N], ec;

void init(int n) {
	ec = 0;
	memset(eh, -1, sizeof(int) * n);
}

void addedge(int u, int v, int c) {
	//cout << u << ' ' << v << ' ' << c << endl;
	edge[ec] = Edge(u, v, c, eh[u]);
	eh[u] = ec++;
	edge[ec] = Edge(v, u, c, eh[v]);
	eh[v] = ec++;
}

LL dis[N * N];
typedef pair<LL, int> PII;
bool vis[N * N];
LL spfa(int s, int t, int n) {
	memset(dis, 0x77, sizeof(LL) * n);
	for (int i = 0; i < n; i++) vis[i] = 0;
	priority_queue<PII> q;
	while (!q.empty()) q.pop();
	dis[s] = 0;
	q.push(PII(0, s));
	while (!q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		if (u == t) return dis[t];
		for (int i = eh[u]; ~i; i = edge[i].nx) {
			Edge &e = edge[i];
			int v = e.v, c = e.c;
			if (dis[v] > dis[u] + c) {
				dis[v] = dis[u] + c;
				q.push(PII(-dis[v], v));
			}
		}
	}
	return dis[t];
}

int mat[N][N];
int main() {
	//freopen("in", "r", stdin);
	int n, m, T;
	scanf("%d", &T);
	while (T-- && ~scanf("%d", &n)) {
		init(n * n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", mat[i] + j);
			}
		}
		int s = 0, t = (n - 1) * (n - 1) + 1;
		for (int i = 1; i < n; i++) {
			addedge(i, t, mat[0][i - 1]);
			addedge(i * (n - 1), t, mat[i - 1][n - 1]);
			addedge(s, (n - 2) * (n - 1) + i, mat[n - 1][i - 1]);
			addedge(s, (i - 1) * (n - 1) + 1, mat[i - 1][0]);
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 1; j < n - 1; j++) addedge(i * (n - 1) + j, i * (n - 1) + j + 1, mat[i][j]);
		}
		for (int i = 0; i < n - 2; i++) {
			for (int j = 1; j < n; j++) addedge((i + 1) * (n - 1) + j, i * (n - 1) + j, mat[i + 1][j - 1]);
		}
		cout << spfa(s, t, n * n) << endl;
	}
}