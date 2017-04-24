#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1 << 9;
const int M = 1 << 12;
struct Edge {
	int u, v, nx;
	Edge() {}
	Edge(int u, int v, int nx) : u(u), v(v), nx(nx) {}
} edge[M];
int eh[N], ec;

void init() {
	memset(eh, -1, sizeof eh);
	ec = 0;
}

void addEdge(int u, int v) {
	//cerr << u << ' ' << v << endl;
	edge[ec] = Edge(u, v, eh[u]);
	eh[u] = ec++;
}

int mx[N], my[N];
bool visit[N];
bool dfs(int x) {
	for (int i = eh[x]; ~i; i = edge[i].nx) {
		int y = edge[i].v;
		if (visit[y]) continue;
		visit[y] = 1;
		if (my[y] == -1 || dfs(my[y])) {
			mx[x] = y;
			my[y] = x;
			return 1;
		}
	}
	return 0;
}

int hungery(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		mx[i] = -1;
	}
	for (int i = 1; i <= m; ++i) {
		my[i] = -1;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		memset(visit, 0, sizeof visit);
		cnt += dfs(i);
	}
	return cnt;
}

struct Star {
	int x, y, z;
	LL p;
	void get() { cin >> x >> y >> z >> p; }
} star[N], temp[N];
bool operator != (const Star &a, const Star &b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
bool cmp(const Star &a, const Star &b) {
	if (a.x - b.x) return a.x < b.x;
	if (a.y - b.y) return a.y < b.y;
	return a.z < b.z;
}

bool isBeside(const Star &a, const Star &b) {
	int sum = 0;
	sum += abs(a.x - b.x);
	sum += abs(a.y - b.y);
	sum += abs(a.z - b.z);
	return sum == 1;
}

int merge(int n) {
	int m = 0;
	memcpy(temp, star, sizeof temp);
	for (int i = 1; i <= n; ++i) {
		if (i == 1 || temp[i] != temp[i - 1]) {
			star[++m] = temp[i];
		} else {
			star[m].p += temp[i].p;
		}
	}
	return m;
}

bool mark[N];
void build(int n, LL value) {
	init();
	memset(mark, 0, sizeof mark);
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (i == j) continue;
			if (isBeside(star[i], star[j]) && star[i].p + star[j].p >= value) {
				Star &a = star[i];
				if (a.x + a.y + a.z & 1) {
					addEdge(i, j);
				} else {
					addEdge(j, i);
				}
				mark[i] = mark[j] = 1;
			}
		}
	}
}

bool check(int n, int k, LL value) {
	int t = hungery(n, n);
	if (n - t > k) return 0;
	for (int i = 1; i <= n; ++i) {
		if (mark[i]) continue;
		if (star[i].p < value) return 0;
	}
	return 1;
}

void work(int n, int k) {
	LL L = 0, R = 100000000000LL, MID, mk = -1;
	while (L <= R) {
		MID = L + R >> 1;
		build(n, MID);
		if (check(n, k, MID)) {
			mk = MID;
			L = MID + 1;
		} else R = MID - 1;
	}
	cerr << "Debug mk " << mk << endl;
	//mk = 11;
	if (mk == -1) cout << -1 << endl;
	else {
		build(n, mk);
		int t = hungery(n, n);
		cout << (n - t) << ' ' << mk << endl;
		for (int i = 0, temp = ec; i < temp; ++i) {
			addEdge(edge[i].v, edge[i].u);
		}
		//for (int i = 1; i <= n; ++i) cerr << mark[i]; cerr << endl;
		//for (int i = 1; i <= n; ++i) cerr << mx[i] << ' ' << my[i] << endl;
		memset(visit, 0, sizeof visit);
		for (int i = 1; i <= n; ++i) {
			if (visit[i]) continue;
			//cerr << mx[i] << ' ' << my[i] << endl;
			if (mx[i] != -1 || my[i] != -1) {
				int j = mx[i] != -1 ? mx[i] : my[i];
				visit[i] = visit[j] = 1;
				cout << (star[i].x + star[j].x) / 2.0 << ' ' << (star[i].y + star[j].y) / 2.0 << ' ' << (star[i].z + star[j].z) / 2.0 << endl;
			} else {
				if (mark[i]) {
					Star &a = star[i], &b = star[edge[eh[i]].v];
					cout << (a.x + b.x) / 2.0 << ' ' << (a.y + b.y) / 2.0 << ' ' << (a.z + b.z) / 2.0 << endl;
				} else {
					cout << star[i].x << ' ' << star[i].y << ' ' << star[i].z << endl;
				}
				visit[i] = 1;
			}
		}
	}
}

int run() {
	int n, k;
	while (cin >> n >> k) {
		for (int i = 1; i <= n; ++i) star[i].get();
		sort(star + 1, star + n + 1, cmp);
		n = merge(n);
		//for (int i = 1; i <= n; ++i) cerr << "Star " << i << ' ' << star[i].x << ' ' << star[i].y << ' ' << star[i].z << ' ' << star[i].p << endl;
		work(n, k);
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	freopen("starbugs.in", "r", stdin);
	freopen("starbugs.out", "w", stdout);
	return run();
}
