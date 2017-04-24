#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
#include <queue>
using namespace std;

const int N = 111;
const int M = 2222;
const int Q = 20;
const long double eps = 1e-8;
const long double inf = 1e15;
int n, m, q;
map<string, int> pos;
int eh[N], tot;
int P[Q];
long double T[Q][N], A[Q], V[Q];
long double C;
long double dist[N];
bool visit[N];

struct Edge {
	int u, v; long double cost; int next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void addedge(int u, int v, long double cost) {
	et[tot].u = u, et[tot].v = v, et[tot].cost = cost, et[tot].next = eh[u];
	eh[u] = tot++;
}

char s_str[50], t_str[50];
int t;
long double spfa(int id, int s, int t, long double vv) {
	for (int i = 1; i <= n; i++) dist[i] = inf;
	queue<int> que;
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			long double cost = et[i].cost / vv;
			if (v == t) {
				dist[t] = min(dist[t], dist[u] + cost);
			} else {
				if (dist[v] > dist[u] + cost + T[id][v]) {
					dist[v] = dist[u] + cost + T[id][v];
					if (!visit[v]) {
						visit[v] = true;
						que.push(v);
					}
				}
			}
		}
	}
	//cout << dist[t] << endl;
	return dist[t];
}

bool check(long double limit) {
	long double sumc = 0;
	for (int i = 1; i <= q; i++) {
		long double c;
		long double l = 0.0, r = C - sumc;
		long double ret = spfa(i, P[i], t, sqrt(r) * A[i] + V[i]);
		if (ret > limit) return false;
		while (l + eps <= r) {
			long double mid = (l + r) / 2.0;
			long double ret = spfa(i, P[i], t, sqrt(mid) * A[i] + V[i]);
			if (ret < limit || fabs(ret - limit) < eps) c = mid, r = mid;
			else l = mid;
		}
		sumc += c;
	}
	return sumc < C || fabs(sumc - C) < eps;
}

void solve() {
	t = pos["Hakurei_Shrine"];
	long double l = 0.0, r = 0.0, ans;
	for (int i = 1; i <= q; i++) {
		r = max(r, spfa(i, P[i], t, V[i]));
	}
	//cout << r << endl;
	while (l + eps < r) {
		long double mid = (l + r) / 2.0;
		if (check(mid)) ans = mid, r = mid;
		else l = mid;
	}
	printf("%.10f\n", (double) ans);
}
int main() {
	while (~scanf("%d%d%d", &n, &m, &q)) {
		init();
		pos.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%s", s_str);
			pos[s_str] = i;
		}
		for (int i = 0; i < m; i++) {
			double cost;
			scanf("%s%s%lf", s_str, t_str, &cost);
			int a = pos[s_str], b = pos[t_str];
			addedge(a, b, cost);
			addedge(b, a, cost);
			//cout << a << " " << b << " " << cost << endl;
		}
		for (int i = 1; i <= q; i++) {
			scanf("%s%s", s_str, t_str);
			P[i] = pos[t_str];
			//cout << i << " " << P[i] << endl;
			scanf("%Lf%Lf", &V[i], &A[i]);
			for (int j = 1; j <= n; j++) {
				scanf("%Lf", &T[i][j]);
			}
		}
		scanf("%Lf", &C);
		solve();
	}
	return 0;
}
