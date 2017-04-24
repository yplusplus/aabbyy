#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 111;
const int inf = 1 << 30;
int n, m1, m2;
struct Edge {
	int v, w, t;
	Edge(int v, int w, int t) : v(v), w(w), t(t) {}
};

vector<Edge> vec[N];
int dist[N][5555];
bool visit[N][5555];

void spfa(int s, int t, int T, int &limit) {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m2; j++) {
			dist[i][j] = inf;
		}
	}
	dist[s][0] = 0;
	queue<int> que;
	que.push(s);
	que.push(0);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		int m = que.front(); que.pop();
		visit[u][m] = false;
		if (m >= limit) continue;
		if (u == t) {
			limit = m;
			continue;
		}
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].v, w = vec[u][i].w;
			int nm = m + vec[u][i].t;
			int tmp = dist[u][m] + w;
			if (tmp > T || tmp >= dist[v][nm]) continue;
			dist[v][nm] = tmp;
			if (!visit[v][nm]) {
				visit[v][nm] = true;
				que.push(v);
				que.push(nm);
			}
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		scanf("%d", &m1);
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m1; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(Edge(b, c, 0));
			vec[b].push_back(Edge(a, c, 0));
		}
		scanf("%d", &m2);
		for (int i = 0; i < m2; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(Edge(b, c, 1));
			vec[b].push_back(Edge(a, c, 1));
		}
		int ans = m2 + 1;
		int s, t, T;
		scanf("%d%d%d", &s, &t, &T);
		spfa(s, t, T, ans);
		if (ans == m2 + 1) puts("Impossible");
		else printf("%d\n", ans);
	}
	return 0;
}
