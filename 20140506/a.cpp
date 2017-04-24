#include <bits/stdc++.h>
using namespace std;

const int N = 111;
const int inf = 1 << 20;
const int M = 20 * N * N;
int a[N][N];
int eh[N], tot;
int pre[N], low[N], dist[N];
int ansflow, anscost;
int n, k;
bool visit[N];

struct Edge {
	int u, v, cost, cap, flow, next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow) {
	Edge e = {u, v, cost, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap) {
	add(u, v, cost, cap, 0);
	add(v, u, -cost, 0, 0);
}

bool spfa(int s, int t) {
	for (int i = 0; i < N; i++) { dist[i] = -inf; }
	pre[s] = -1; dist[s] = 0; low[s] = inf;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int i = eh[u]; i != -1; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] < dist[u] + et[i].cost) {
				dist[v] = dist[u] + et[i].cost;
				pre[v] = i;
				low[v] = min(low[u], et[i].cap - et[i].flow);
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dist[t] != -inf;
	//return dist[t] > 0;
}

void mcmf(int s, int t) {
	ansflow = anscost = 0;
	while (spfa(s, t)) {
		anscost += low[t] * dist[t];
		ansflow += low[t];
		int x = pre[t];
		while (x != -1) {
			et[x].flow += low[t];
			et[x ^ 1].flow -= low[t];
			x = pre[et[x].u];
		}
	}
}

int main() {
	freopen("assignment.in", "r", stdin);
	freopen("assignment.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n >> k;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			sum += a[i][j];
		}
	}
	init();
	int s = n + n, t = s + 1;
	for (int i = 0; i < n; i++) {
		addedge(s, i, 0, n - k);
		addedge(i + n, t, 0, n - k);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			addedge(i, j + n, a[i][j], 1);
		}
	}
	mcmf(s, t);
	cout << sum - anscost << endl;
	return 0;
}
