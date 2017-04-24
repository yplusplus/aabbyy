#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
const int M = 22222;
const int inf = 1 << 28;
#define fi first
#define se second
int n, m;
struct Edge {
	int u, v , d, c;
	void read() {
		scanf("%d%d%d%d", &u, &v, &d, &c);
	}
} edge[M];

int dist[N];
bool visit[N];
vector<pair<int, int> > vec[N];
void spfa(int s) {
	memset(visit, false, sizeof(visit));
	for (int i = 1; i <= n; i++) dist[i] = inf;
	dist[s] = 0;
	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].fi;
			if (dist[v] > dist[u] + vec[u][i].se) {
				dist[v] = dist[u] + vec[u][i].se;
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
}

bool cmp(const Edge &a, const Edge &b) {
	return a.c < b.c;
}

int solve() {
	spfa(1);
	sort(edge, edge + m, cmp);
	int ans = 0;
	for (int i = 0; i < m; i++) {
		int a = edge[i].u, b = edge[i].v;
		if (dist[a] < dist[b]) swap(a, b);
		if (dist[a] - dist[b] == edge[i].d) {
			if (!visit[a]) {
				visit[a] = true;
				ans += edge[i].c;
			}
		}
	}
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &m), n + m) {
		for (int i = 1; i <= n; i++) {
			vec[i].clear();
		}
		for (int i = 0; i < m; i++) {
			edge[i].read();
			vec[edge[i].u].push_back(make_pair(edge[i].v, edge[i].d));
			vec[edge[i].v].push_back(make_pair(edge[i].u, edge[i].d));
		}
		printf("%d\n", solve());
	}
	return 0;
}

