#include <bits/stdc++.h>
using namespace std;

const int N = 1111;
const int M = 1222222;
int eh[N], tot;
int dist[N], cur[N];
int n, m, k;
struct Edge {
	int u, v;
	long long cap, flow;
	int next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, long long cap, long long flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, long long cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	que.push(s);
	memset(dist, -1, sizeof(dist));
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (dist[v] == -1 && et[i].cap > et[i].flow) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

long long dfs(int u, int t, long long d) {
	if (u == t) return d;
	long long l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (dist[v] == dist[u] + 1 && et[i].cap > et[i].flow) {
			long long tmp = dfs(v, t, min(l, 0LL + et[i].cap - et[i].flow));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

long long Dinic(int s, int t) {
	long long res = 0;
	while (bfs(s, t)) {
		memcpy(cur, eh, sizeof(cur));
		res += dfs(s, t, 1LL << 60);
	}
	return res;
}

int x[N], y[N];
int state[N];
int P;
void solve() {
	int s = 0, t = n + 1;
	long long sum = 0;
	init();
	for (int i = 1; i <= n; i++) {
		sum += (x[i] & y[i]);
		if (state[i]) {
			addedge(i, t, x[i] & y[i]);
		} else addedge(s, i, x[i] & y[i]);
	}
	for (int i = 1; i <= n; i++) {
		if (state[i]) continue;
		//addedge(i + n, t, x[i] & y[i]);
		for (int j = 1; j <= n; j++) {
			if (state[j] == 0) continue;
			int d = x[i] ^ y[i] ^ x[j] ^ y[j];
			d = __gcd(d, P);
			if (d == 1) {
				addedge(i, j, 1LL << 60);
			}
		}
	}
	long long ans = Dinic(s, t);
	ans = sum - ans;
	cout << ans << endl;
}

int main() {
	while (~scanf("%d%d", &n, &P)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &x[i], &y[i]);
			state[i] = (x[i] ^ y[i]) & 1;
		}
		solve();
	}
	return 0;
}
