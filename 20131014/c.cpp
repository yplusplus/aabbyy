#include <bits/stdc++.h>

using namespace std;

const int N = 2222;
const int M = 2222222;
int ans[N >> 1];

struct Two {
	struct Edge {
		int v, nx;
		Edge() {}
		Edge(int v, int nx) : v(v), nx(nx) {}
	} edge[M];
	int eh[N], ec, n;
	int stk[N], top;
	bool vis[N];
	void init(int _n) {
		n = _n;
		memset(eh, -1, sizeof(eh));
		ec = 0;
	}
	void addedge(int u, int v) {
		edge[ec] = Edge(v, eh[u]);
		eh[u] = ec++;
	}
	bool dfs(int u) {
		if (vis[u ^ 1]) return 0;
		if (vis[u]) return 1;
		vis[stk[++top] = u] = 1;
		ans[u >> 1] = (u & 1) + 1;
		for (int i = eh[u]; ~i; i = edge[i].nx) {
			int v = edge[i].v;
			if (!dfs(v)) return 0;
		}
		return 1;
	}
	bool test() {
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			if (!vis[i << 1] && !vis[i << 1 | 1]) {
				top = -1;
				if (!dfs(i << 1)) {
					while (~top) vis[stk[top--]] = 0;
					if (!dfs(i << 1 | 1)) return 0;
				}
			}
		}
		return 1;
	}
} two;

typedef pair<int, int> Node;
#define x first
#define y second
Node node[N];

void work(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (node[i << 1].x == node[j << 1].x || node[i << 1].y == node[j << 1].y)
				two.addedge(i << 1, j << 1 | 1), two.addedge(j << 1, i << 1 | 1);
			if (node[i << 1 | 1].x == node[j << 1].x || node[i << 1 | 1].y == node[j << 1].y)
				two.addedge(i << 1 | 1, j << 1 | 1), two.addedge(j << 1, i << 1);
			if (node[i << 1].x == node[j << 1 | 1].x || node[i << 1].y == node[j << 1 | 1].y)
				two.addedge(i << 1, j << 1), two.addedge(j << 1 | 1, i << 1 | 1);
			if (node[i << 1 | 1].x == node[j << 1 | 1].x || node[i << 1 | 1].y == node[j << 1 | 1].y)
				two.addedge(i << 1 | 1, j << 1), two.addedge(j << 1 | 1, i << 1);
		}
	}
	two.test();
	for (int i = 0; i < n; i++) {
		if (i) putchar(' ');
		printf("%d", ans[i]);
	}
	puts("");
}

int main() {
	//freopen("in", "r", stdin);
	int n;
	while (~scanf("%d", &n)) {
		int x, y, z;
		two.init(n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &x, &y, &z);
			node[i << 1] = Node(i, x - 1);
			node[i << 1 | 1] = Node(y - 1, z - 1);
		}
		work(n);
	}
	return 0;
}

