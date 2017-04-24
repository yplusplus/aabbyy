#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 9;
const int M = N * N;

#define FOR(i, u) for (int i = u; ~i; i = edge[i].nx)
struct HK {
	struct Edge {
		int u, v, nx;
		Edge() {}
		Edge(int u, int v, int nx) : u(u), v(v), nx(nx) {}
	} edge[M];
	int eh[N], ec, n, m, forbid;
	void init(int a, int b) {
		n = a, m = b;
		for (int i = 1; i <= a; ++i) eh[i] = -1;
		ec = 0;
	}
	void addedge(int u, int v) {
		edge[ec] = Edge(u, v, eh[u]);
		eh[u] = ec++;
	}
	int mx[N], my[N];
	int dx[N], dy[N];
	bool bfs() {
		bool find = 0;
		queue<int> q;
		for (int i = 1; i <= n; ++i) {
			dx[i] = 0;
			if (i == forbid) continue;
			if (mx[i] == -1) q.push(i);
		}
		for (int i = 1; i <= m; ++i) dy[i] = 0;
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			FOR(i, eh[x]) {
				int y = edge[i].v;
				if (dy[y] == 0) {
					dy[y] = dx[x] + 1;
					if (my[y] == -1) find = 1;
					else {
						dx[my[y]] = dy[y] + 1;
						q.push(my[y]);
					}
				}
			}
		}
		//cout << "dx "; for (int i = 1; i <= n; ++i) cout << dx[i] << ' '; cout << endl;
		//cout << "dy "; for (int i = 1; i <= m; ++i) cout << dy[i] << ' '; cout << endl;
		return find;
	}
	bool dfs(int x) {
		if (x == forbid) return 0;
		FOR(i, eh[x]) {
			int y = edge[i].v;
			if (dy[y] == dx[x] + 1) {
				dy[y] = 0;
				if (my[y] == -1 || dfs(my[y])) {
					mx[x] = y;
					my[y] = x;
					return 1;
				}
			}
		}
		return 0;
	}
	int run() {
		int c = forbid = 0;
		for (int i = 1; i <= n; ++i) mx[i] = -1;
		for (int i = 1; i <= m; ++i) my[i] = -1;
		while (bfs()) for (int i = 1; i <= n; ++i) if (mx[i] == -1) c += dfs(i);
		//for (int i = 1; i <= n; ++i) cout << i << ' ' << mx[i] << endl;
		return c;
	}
	bool check(int x) {
		if (mx[x] == -1) return 1;
		int m1 = x, m2 = mx[x];
		mx[m1] = -1;
		my[m2] = -1;
		forbid = x;
		bool res = bfs();
		mx[m1] = m2;
		my[m2] = m1;
		return res;
	}
} hk;

int x[M], y[M];

int run() {
	int n, m, k;
	while (cin >> n >> m >> k) {
		for (int i = 0; i < k; ++i) cin >> x[i] >> y[i];
		hk.init(n, m);
		for (int i = 0; i < k; ++i) hk.addedge(x[i], y[i]);
		hk.run();
		for (int i = 1; i <= n; ++i) cout.put(hk.check(i) ? 'P' : 'N');
		cout << endl;
		hk.init(m, n);
		for (int i = 0; i < k; ++i) hk.addedge(y[i], x[i]);
		hk.run();
		for (int i = 1; i <= m; ++i) cout.put(hk.check(i) ? 'P' : 'N');
		cout << endl;
	}
	return 0;
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(0);
	return run();
}
