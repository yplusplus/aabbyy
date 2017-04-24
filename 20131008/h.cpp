#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 55555;
const int M = 111111;
int n, m;
LL s;

struct Edge {
	int u, v, d, id;
	Edge() {}
	Edge(int u, int v, int d, int id) : u(u), v(v), d(d), id(id) {}
} edge[M];

inline bool cmp(Edge a, Edge b) { return a.d > b.d;}

struct MFS {
	int fa[N];
	void init() { for (int i = 0; i <= n; i++) fa[i] = i;}
	int find(int x) { return fa[x] = fa[x] == x ? x : find(fa[x]);}
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return 0;
		fa[fx] = fy;
		return 1;
	}
} mfs;

bool mk[M];
int ans[M], top;

void mst() {
	sort(edge, edge + m, cmp);
	for (int i = 1; i <= m; i++) mk[i] = 0;
	mfs.init();
	for (int i = 0; i < m; i++) {
		Edge &e = edge[i];
		if (mfs.merge(e.u, e.v)) mk[i] = 1;
	}
}

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0);
	bool pnt = 0;
	while (cin >> n >> m >> s) {
		if (pnt) cout << endl;
		else pnt = 1;
		for (int i = 0; i < m; i++) {
			cin >> edge[i].u >> edge[i].v >> edge[i].d;
			edge[i].id = i + 1;
		}
		mst();
		top = -1;
		for (int i = m - 1; i >= 0; i--) {
			if (mk[i]) continue;
			Edge &e = edge[i];
			if (s >= e.d) ans[++top] = e.id, s -= e.d;
			else break;
		}
		cout << top + 1 << endl;
		while (top >= 0) {
			cout << ans[top--];
			if (top < 0) cout << endl;
			else cout << ' ';
		}
	}
	return 0;
}
