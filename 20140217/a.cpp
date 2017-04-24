#include <bits/stdc++.h>
using namespace std;

const int N = 222;
const int M = 222222;
#define fi first
#define se second
pair<int, int> white[N];
pair<int, int> black[N];
const int inf = 1 << 30;
int n;
int eh[N], tot;
int pre[N];
bool visit[N];
double dist[N];

struct Edge {
	int u, v, cap, flow, next;
	double cost;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, double cost, int cap, int flow) {
	Edge e = {u, v, cost, cap, flow, eh[u]};
	e.u = u;
	e.v = v;
	e.cost = cost;
	e.cap = cap;
	e.flow = flow;
	e.next = eh[u];
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, double cost, int cap) {
	add(u, v, cost, cap, 0), add(v, u, -cost, 0, 0);
}

bool spfa(int s, int t) {
	for (int i = s; i <= t; i++) dist[i] = 1e12;
	queue<int> que;
	que.push(s);
	dist[s] = 0;
	pre[s] = -1;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
				pre[v] = i;
				dist[v] = dist[u] + et[i].cost;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dist[t] < 1e10;
}

int sq(int x) {
	return x * x;
}

double get_distance(const pair<int, int> &a, const pair<int, int> &b) {
	return sqrt(0.0 + sq(a.fi - b.fi) + sq(a.se - b.se));
}

int mcmf(int s, int t) {
	int anscost = 0;
	while (spfa(s, t)) {
		//cout << "aug" << endl;
		//cout << "aug" << endl;
		anscost += dist[t];
		int x = pre[t];
		while (x != -1) {
			et[x].flow ++;
			et[x ^ 1].flow --;
			x = pre[et[x].u];
		}
	}
	return anscost;
}

int match[N];
void solve() {
	init();
	int s = 0, t = 2 * n + 1;
	for (int i = 1; i <= n; i++) {
		addedge(s, i, 0, 1);
		addedge(n + i, t, 0, 1);
		for (int j = 1; j <= n; j++) {
			addedge(i, j + n, get_distance(white[i], black[j]), 1);
		}
	}
	int ans = mcmf(s, t);
	for (int i = 1; i <= n; i++) {
		for (int j = eh[i]; ~j; j = et[j].next) {
			if (et[j].cap == et[j].flow && et[j].v > n) {
				match[i] = et[j].v - n;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d\n", match[i]);
	}
}

int main() {
	bool first = true;
	while (~scanf("%d", &n)) {
		if (first) {
			first = false;
		} else puts("");
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &white[i].fi, &white[i].se);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &black[i].fi, &black[i].se);
		}
		solve();
	}
	return 0;
}
