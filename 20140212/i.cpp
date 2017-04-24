#include <bits/stdc++.h>
using namespace std;

int n, m, p;
const int N = 11111;
const int M = 555555;
pair<int, int> att[N];
const int inf = 1 << 30;
int eh[N], tot;
int val[N];
int s, t;
int anscost, ansflow;
bool cmp(int x, int y) {
	return att[x].first < att[y].first;
}

struct Edge {
	int u, v, cost, cap, flow, id, next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cost, int cap, int flow, int id) {
	Edge e = {u, v, cost, cap, flow, id, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cost, int cap, int id) {
	add(u, v, cost, cap, 0, id);
	add(v, u, -cost, 0, 0, 0);
}

bool visit[N];
int dist[N];
bool spfa(int s, int t) {
	for (int i = 0; i <= m + 1; i++) { visit[i] = false; dist[i] = inf; }
	dist[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] > dist[u] + et[i].cost) {
				dist[v] = dist[u] + et[i].cost;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	for (int i = 0; i <= t; i++) dist[i] = dist[t] - dist[i];
}

int dfs(int u, int t, int d) {
	if (t == u) {
		return anscost += d * dist[s], ansflow += d, d;
	}
	int l = d;
	visit[u] = true;
	for (int i = eh[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (!visit[v] && dist[u] == dist[v] + et[i].cost && et[i].cap > et[i].flow) {
			int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

bool modify_label(int n) {
	int d = inf;
	for (int u = 0; u < n; u++) {
		if (visit[u]) {
			for (int j = eh[u]; ~j; j = et[j].next) {
				int v = et[j].v;
				if (et[j].cap > et[j].flow && !visit[v]) d = min(d, dist[v] + et[j].cost - dist[u]);


			}
		}
	}
	if (d == inf) return false;
	for (int u = 0; u < n; u++) if (visit[u]) dist[u] += d;
	return true;
}


void mcmf(int s, int t, int n) {
	anscost = ansflow = 0;
	spfa(s, t);
	do {
		do {
			memset(visit, false, sizeof(visit));
		} while (dfs(s, t, inf));
	} while (modify_label(n));
}

void solve() {
	init();
	s = 0, t = m + 1;
	for (int i = 0; i < t; i++) addedge(i, i + 1, 0, p, 0);
	for (int i = 1; i <= n; i++) {
		int st = att[i].first, ed = att[i].second;
		addedge(st, ed + 1, -val[i], 1, i);
	}
	mcmf(s, t, t + 1);
	vector<int> vec;
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += val[i];
	printf("%d\n", sum + anscost);
	for (int i = 0; i < tot; i++) {
		if (et[i].flow == et[i].cap && et[i].id) {
			vec.push_back(et[i].id);
		}
	}
	memset(visit, false, sizeof(visit));
	sort(vec.begin(), vec.end(), cmp);
	for (int i = 0; i < p; i++) {
		int end = -1;
		vector<int> bag;
		for (int j = 0; j < vec.size(); j++) {
			int id = vec[j];
			if (visit[id] || att[id].first <= end) continue;
			end = att[id].second;
			bag.push_back(id);
			visit[id] = true;
		}
		if (bag.empty()) puts("");
		else {
			for (int i = 0; i < bag.size(); i++) {
				printf("%d%c", bag[i], i + 1 == bag.size() ? '\n' : ' ');
			}
		}
	}
	puts("");
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &p), n + m + p) {
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &att[i].first, &att[i].second);
			scanf("%d", &val[i]);
		}
		solve();
	}
	return 0;
}
