#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> V2I;
typedef vector<bool> VB;
struct Edge {
	int u, v, d, nx;
	Edge() {}
	Edge(int u, int v, int d, int nx) : u(u), v(v), d(d), nx(nx) {}
} ;
typedef vector<Edge> VE;
VE edge;
VI eh, id;
V2I dist;
int ec;

int n, m, l;
void init() {
	if (id.size() < n + 1) id.resize(n + 1);
	eh.clear();
	eh.resize(m + 1, -1); // start from 1
	dist.clear();
	dist.resize(m + 1, VI(m + 1, -1));
	for (int i = 1; i <= m; ++i) dist[i][i] = 0;
	if (edge.size() < (l << 1)) edge.resize(l << 1);
	ec = 0;
}

void addedge(int u, int v, int d) {
	edge[ec] = Edge(u, v, d, eh[u]);
	eh[u] = ec++;
	edge[ec] = Edge(v, u, d, eh[v]);
	eh[v] = ec++;
}

void spfa(int x, VI &d) {
	VB inq(m + 1, 0);
	int u, v;
	queue<int> q;
	q.push(x);
	inq[x] = 1;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		inq[u] = 0;
		for (int i = eh[u]; ~i; i = edge[i].nx) {
			Edge &e = edge[i];
			v = e.v;
			if (-1 == d[v] || d[v] > d[u] + e.d) {
				d[v] = d[u] + e.d;
				if (inq[v]) continue;
				q.push(v);
				inq[v] = 1;
			}
		}
	}
}

int get_dist(int a, int b, int c, int x) {
	int ans = INT_MAX;
	for (int i = 1; i <= m; ++i) {
		if (~dist[a][x] && ~dist[b][x] && ~dist[c][x]) {
			ans = min(dist[a][x] + dist[b][x] + dist[c][x], ans);
		}
	}
	return ans;
}

void query(int x, int y, int z) {
	int ans = INT_MAX;
	spfa(x, dist[x]);
	spfa(y, dist[y]);
	spfa(z, dist[z]);
	for (int i = 1; i <= m; ++i) ans = min(get_dist(x, y, z, i), ans);
	if (INT_MAX == ans) cout << "Impossible to connect!" << endl;
	else cout << "The minimum cost for this line is " << ans << "." << endl;
}

void print_mat() {
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= m; ++j) cout << dist[i][j] << ' ';
		cout << endl;
	}
}

int run() {
	int cas = 0;
	while (cin >> n >> m >> l) {
		init();
		for (int i = 1; i <= n; ++i) cin >> id[i];
		int x, y, z;
		for (int i = 0; i < l; ++i) {
			cin >> x >> y >> z;
			addedge(x, y, z);
		}
		//for (int i = 1; i <= m; ++i) spfa(i, dist[i]);
		//print_mat();
		int q;
		cin >> q;
		cout << "Case #" << ++cas << endl;
		for (int i = 1; i <= q; ++i) {
			cout << "Line " << i << ": ";
			cin >> x >> y >> z;
			query(id[x], id[y], id[z]);
		}
	}
	return 0;
}

int main() {
	//freopen("in_a", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
