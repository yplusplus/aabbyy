#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int N = 1111;
const int inf = 1 << 30;
struct Edge {
	int v, w, id;
	Edge() {}
	Edge(int _v, int _w, int _id) : v(_v), w(_w), id(_id) {}
};

vector<Edge> vec[N];
pair<int, int> pre[N];
int dist[N];
bool visit[N];
int n, m;
int spfa(int s, int t, int forbid = -1) {
	for (int i = 1; i <= n; i++) dist[i] = inf;
	dist[1] = 0;
	deque<int> que;
	que.push_back(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop_front();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].v, w = vec[u][i].w, id = vec[u][i].id;
			if (id == forbid) continue;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pre[v] = make_pair(id, u);
				if (!visit[v]) {
					visit[v] = true;
					if (que.empty() || dist[v] > dist[que.front()]) que.push_back(v);
					else que.push_front(v);
				}
			}
		}
	}
	return dist[t];
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(Edge(b, c, i));
			vec[b].push_back(Edge(a, c, i));
		}
		int ans = spfa(1, n);
		vector<int> path;
		int x = n;
		while (x != 1) {
			path.push_back(pre[x].first);
			x = pre[x].second;
		}
		for (int i = 0; i < path.size() && ans != inf; i++) {
			ans = max(ans, spfa(1, n, path[i]));
		}
		if (ans == inf) ans = -1;
		printf("%d\n", ans);
	}
}

