#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef double DB;
const int N = 222;
const int M = 1111;
const DB FINF = 1e55;
DB X[N][3];

struct Edge {
	int u, v, nx;
	DB d;
	Edge() {}
	Edge(int u, int v, DB d, int nx) : u(u), v(v), d(d), nx(nx) {}
} edge[M];
int eh[N], ec;

void init() {
	memset(eh, -1, sizeof(eh));
	ec = 0;
}

void addedge(int u, int v, DB d) {
	edge[ec] = Edge(u, v, d, eh[u]);
	eh[u] = ec++;
}

template<class T> T sqr(T x) { return x * x; }
DB dist(int i, int j) { return sqrt(sqr((X[i][0] - X[j][0]) * 5) + sqr(X[i][1] - X[j][1]) + sqr(X[i][2] - X[j][2])); }

int pre[N][N];
DB dis[N];
bool inq[N];
void get_sp(int id) {
	queue<int> q;
	memset(inq, 0, sizeof(inq));
	for (int i = 0; i < N; i++) dis[i] = FINF;
	dis[id] = 0;
	q.push(id);
	inq[id] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = eh[u]; ~i; i = edge[i].nx) {
			Edge &e = edge[i];
			if (dis[e.v] > dis[u] + e.d) {
				dis[e.v] = dis[u] + e.d;
				pre[id][e.v] = u;
				if (inq[e.v]) continue;
				q.push(e.v);
				inq[e.v] = 1;
			}
		}
	}
}

void work(int u, int v) {
	int cur = v;
	stack<int> stk;
	while (cur != u) {
		stk.push(cur);
		cur = pre[u][cur];
	}
	printf("%d", u);
	while (!stk.empty()) {
		printf(" %d", stk.top());
		stk.pop();
	}
	puts("");
}

int main() {
	//freopen("in", "r", stdin);
	int n, m;
	bool pnt = 0;
	while (~scanf("%d%d", &n, &m)) {
		if (pnt) puts("");
		pnt = 1;
		int u, v;
		char buf[22];
		init();
		for (int i = 0; i < n; i++) for (int j = 0; j < 3; j++) scanf("%lf", X[i] + j);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%s", &u, &v, buf);
			if (*buf == 'w' || *buf == 's') {
				addedge(u, v, dist(u, v));
				addedge(v, u, dist(u, v));
			} else if (*buf == 'e') {
				addedge(u, v, 1);
				addedge(v, u, dist(u, v) * 3);
			} else if (*buf == 'l') {
				addedge(u, v, 1);
				addedge(v, u, 1);
			}
		}
		for (int i = 0; i < n; i++) get_sp(i);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			work(u, v);
		}
	}
	return 0;
}

