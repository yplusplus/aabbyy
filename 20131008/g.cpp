#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 111;
const int M = 1111;
const double eps = 1e-6;
int n, m;
int eh[N], tot, cur[N];
int dist[N];
struct EE {
	int u, v, cost, id;
	void read(int _id) {
		id = _id;
		cin >> u >> v >> cost;
	}
} edge[M];

struct Edge {
	int u, v;
	double cap;
	int id;
	int next;
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, double cap, int id) {
	et[tot].u = u;
	et[tot].v = v;
	et[tot].cap = cap;
	et[tot].next = eh[u];
	et[tot].id = id;
	eh[u] = tot++;
}

void addedge(int u, int v, double cap, int id) {
	add(u, v, cap, id), add(v, u, cap, id);
}

bool bfs(int s, int t) {
	queue<int> que;
	memset(dist, -1, sizeof(dist));
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > eps && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

double dfs(int u, int t, double d) {
	if (u == t) return d;
	double l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > eps && dist[v] == dist[u] + 1) {
			double tmp = dfs(v, t, min(l, et[i].cap));
			et[i].cap -= tmp;
			et[i ^ 1].cap += tmp;
			l -= tmp;
			if (l < eps) break;
		}
	}
	return d - l;
}

double Dinic(int s, int t) {
	double res = 0;
	while (bfs(s, t)) {
		//cout << s << " " << t << endl;
		memcpy(cur, eh, sizeof(cur));
		res += dfs(s, t, 1e10);
	}
	return res;
}

bool check(double mid) {
	init();
	double sum = 0.0;
	//cout << mid << endl;
	for (int i = 0; i < m; i++) {
		if (edge[i].cost < mid) sum += edge[i].cost - mid;
		else {
			addedge(edge[i].u, edge[i].v, edge[i].cost - mid, edge[i].id);
		}
	}
	sum += Dinic(1, n);
	return sum < eps;
}

int main() {
	while (cin >> n >> m) {
		double l = 0.0, r = 0.0;
		for (int i = 0; i < m; i++) edge[i].read(i), r = max(r, edge[i].cost * 1.0);
		double ans = 0.0;
		for (int i = 0; i < 50; i++) {
			double mid = (l + r) / 2.0;
			if (check(mid)) ans = mid, r = mid;
			else l = mid;
		}
		check(ans);
		vector<int> vec;
		for (int i = 0; i < tot; i += 2) {
			int u = et[i].u, v = et[i].v, id = et[i].id;
			if (dist[v] == -1 && dist[u] == -1) continue;
			if (dist[v] >= 0 && dist[u] >= 0) continue;
			vec.push_back(id);
		}
		for (int i = 0; i < m; i++) {
			if (edge[i].cost < ans) vec.push_back(edge[i].id);
		}
		sort(vec.begin(), vec.end());
		//cout << ans << endl;
		cout << vec.size() << endl;
		for (int i = 0; i < vec.size(); i++) {
			printf("%d%c", vec[i] + 1, i == vec.size() - 1 ? '\n' : ' ');
		}
	}
}

