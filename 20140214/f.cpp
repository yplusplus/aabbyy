#include <bits/stdc++.h>
using namespace std;

const int N = 6666;
const int M = 555555;
map<string, int> mp;
int alloc;
int n, m;
bool visit[N];
int cnt[N];
int eh[N], tot, cur[N];
int dist[N];
int dd;

struct Edge {
	int u, v, cap, flow, next;
} et[M];

void init() {
	tot = 0;
	memset(eh, -1, sizeof(eh));
}

void add(int u, int v, int cap, int flow) {
	Edge e = {u, v, cap, flow, eh[u]};
	et[tot] = e;
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}


int get_id(const string &name) {
	if (mp.count(name)) { return mp[name]; }
	return mp[name] = ++alloc;
}

bool bfs(int s, int t) {
	for (int i = 0; i <= t; i++) dist[i] = -1;
	queue<int> que;
	que.push(s);
	dist[s] = 0;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = eh[u]; ~i; i = et[i].next) {
			int v = et[i].v;
			if (et[i].cap > et[i].flow && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				que.push(v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int u, int t, int d) {
	if (u == t) return d;
	int l = d;
	for (int &i = cur[u]; ~i; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > et[i].flow && dist[u] + 1 == dist[v]) {
			int tmp = dfs(v, t, min(et[i].cap - et[i].flow, l));
			et[i].flow += tmp;
			et[i ^ 1].flow -= tmp;
			l -= tmp;
			if (l == 0) break;
		}
	}
	return d - l;
}

int Dinic(int s, int t) {
	int res = 0;
	while (bfs(s, t)) {
		memcpy(cur, eh, sizeof(eh));
			res += dfs(s, t, 1 << 30);
	}
	return res;
}
int main() {
	char name[20], result[20];
	while (~scanf("%d%d", &n, &m)) {
		alloc = 0;
		mp.clear();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%s", name); u = get_id(name);
			scanf("%s", name); v = get_id(name);
			scanf("%s", result);
			if (result[0] == 'w') cnt[u]++;
			else cnt[v]++;
		}
		dd = get_id("DD");
		int p;
		scanf("%d", &p);
		int other = 0;
		init();
		for (int i = 0; i < p; i++) {
			int u, v;
			scanf("%s", name); u = get_id(name);
			scanf("%s", name); v = get_id(name);
			if (u == dd || v == dd) cnt[dd]++;
			else {
				other++;
				addedge(u, other + n, 1);
				addedge(v, other + n, 1);
			}
		}
		int s = 0, t = n + other + 1;
		for (int i = 1; i <= other; i++) {
			addedge(i + n, t, 1);
		}
		bool found = false;
		for (int i = 1; i <= n && !found; i++) {
			if (i == dd) continue;
			int delta = cnt[dd] - 1 - cnt[i];
			if (delta < 0) found = true;
			addedge(s, i, delta);
		}

		if (found) {
			puts("No");
		} else {
			int ret = Dinic(s, t);
			if (ret == other) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
