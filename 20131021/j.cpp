#include <bits/stdc++.h>
using namespace std;
const int N = 11111;
struct Edge {
	int v, s, l, id;
	Edge(int v, int s, int l, int id) : v(v), s(s), l(l), id(id) {}
	Edge() {}
};

vector<Edge> vec[N];
double dist[N];
pair<int, int> pre[N];
bool visit[N];
int n, m;
double T;

bool check(double mid) {
	queue<int> que;
	for (int i = 1; i <= n; i++) dist[i] = 1e300, pre[i] = make_pair(-1, -1);
	memset(visit, false, sizeof(visit));
	dist[1] = 0;
	que.push(1);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].v;
			double s = vec[u][i].s, l = vec[u][i].l;
			double t = dist[u] + l / (s + mid);
			if (dist[v] > t) {
				dist[v] = t;
				pre[v] = make_pair(u, vec[u][i].id);
				if (!visit[v]) {
					visit[v] = true;
					que.push(v);
				}
			}
		}
	}
	return dist[n] < T || fabs(dist[n] - T) < 1e-8;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < m; i++) {
			int u, v, s, l;
			scanf("%d%d%d%d", &u, &v, &s, &l);
			vec[u].push_back(Edge(v, s, l, i + 1));
			vec[v].push_back(Edge(u, s, l, i + 1));
		}
		scanf("%lf", &T);
		double ans = -1;
		double l = 0, r = 1e12;
		for (int i = 0; i < 60; i++) {
			double mid = (l + r) / 2.0;
			//cout << mid << endl;
			if (check(mid)) ans = mid, r = mid;
			else l = mid;
		}
		check(ans);
		vector<int> path;
		pair<int, int> tmp = pre[n];
		while (tmp.second != -1) {
			path.push_back(tmp.second);
			tmp = pre[tmp.first];
		}
		printf("%.8f %d\n", ans, (int) path.size());
		reverse(path.begin(), path.end());
		for (int i = 0; i < path.size(); i++) {
			printf("%d%c", path[i], i == path.size() - 1 ? '\n' : ' ');
		}
	}
	return 0;
}

