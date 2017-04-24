#include <bits/stdc++.h>
using namespace std;

const int N = 25555;
const int M = 1000000;

bool visit[N];
int dist[N], d[N];
vector<pair<int, int> > vec[N];
int n, m;
int eh[N], tot;
int cnt[N];
int cur[N];

struct Edge {
	int u, v, cap, flow, next;
	Edge() {}
	Edge(int u, int v, int cap, int flow, int next) : u(u), v(v), cap(cap), flow(flow), next(next) {}
} et[M];

void init() {
	memset(eh, -1, sizeof(eh));
	tot = 0;
}

void add(int u, int v, int cap, int flow) {
	et[tot] = Edge(u, v, cap, flow, eh[u]);
	eh[u] = tot++;
}

void addedge(int u, int v, int cap) {
	add(u, v, cap, 0), add(v, u, 0, 0);
}

bool bfs(int s, int t) {
	queue<int> que;
	for (int i = 0; i <= n; i++) { dist[i] = -1; }
	dist[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = eh[u]; i != -1; i = et[i].next) {
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
	for (int &i = cur[u]; i != -1; i = et[i].next) {
		int v = et[i].v;
		if (et[i].cap > et[i].flow && dist[v] == dist[u] + 1) {
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
		for (int i = 0; i <= n; i++) { cur[i] = eh[i]; }
		res += dfs(s, t, INT_MAX);
	}
	return res;
}

void spfa(int s) {
	for (int i = 1; i <= n; i++) { d[i] = INT_MAX; visit[i] = false; }
	queue<int> que;
	d[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first, w = vec[u][i].second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				if (!visit[v]) {
					que.push(v);
					visit[v] = true;
				}
			}
		}
	}
}

vector<pair<int, int> > edge;
void build() {
	init();
	for (int i = 0; i < edge.size(); i++) {
		int u = edge[i].first, v = edge[i].second;
		addedge(u, v, 1);
	}
}

void solve() {
	spfa(1);
	int ans = 0;
	ans += cnt[1];
	cnt[1] = 0;
	edge.clear();
	for (int i = 1; i <= n; i++) {
		int u = i;
		for (int j = 0; j < vec[i].size(); j++) {
			int v = vec[i][j].first, w = vec[i][j].second;
			if (d[u] == d[v] + w) {
				edge.push_back(pair<int, int>(u, v));
				//cout << u << " -> " << v << endl;
			}
		}
	}
	//for (int i = 1; i <= n; i++) { cout << i << " " << d[i] << endl; }
	vector<pair<int, int> > bag;
	for (int i = 2; i <= n; i++) { bag.push_back(pair<int, int>(d[i], i)); }
	sort(bag.begin(), bag.end());
	int s = 0, t = 1;
	//cout << "12312323" << endl;
	for (int i = 0, j; i < bag.size(); i = j) {
		build();
		j = i;
		//cout << i << endl;
		while (j < bag.size() && bag[j].first == bag[i].first) {
			int tmp = bag[j].second;
			if (cnt[tmp]) {
				addedge(s, tmp, cnt[tmp]);
				//cout << tmp << " " << cnt[tmp] << endl;
			}
			j++;
		}
		//cout << "j = " << j << endl;
		ans += Dinic(s, t);
		//cout << i << endl;
	}
	printf("%d\n", ans);
}

int main() {
	int k;
	while (~scanf("%d%d%d", &n, &m, &k)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(pair<int, int>(b, c));
			vec[b].push_back(pair<int, int>(a, c));
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < k; i++) {
			int x;
			scanf("%d", &x);
			cnt[x]++;
		}
		//for (int i = 1; i <= n; i++) { cout << i << " " << cnt[i] << endl; }
		solve();
	}
	return 0;
}
