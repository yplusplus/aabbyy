#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int N = 11111;
int dist[N][2];
bool visit[N][2];
int n, m;
vector<pair<int, int> > vec[N];

bool check_min(int &a, int b) {
	if (b == -1) return false;
	if (a == -1 || b < a) {
		a = b;
		return true;
	}
	return false;
}

void solve(int s, int t) {
	memset(dist, -1, sizeof(dist));
	dist[s][0] = dist[s][1] = 0;
	queue<int> que;
	que.push(s); que.push(0);
	que.push(s); que.push(1);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		int mode = que.front(); que.pop();
		visit[u][mode] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			int mo = vec[u][i].second;
			if (check_min(dist[v][mo], dist[u][mode] + (mode ^ mo))) {
				if (!visit[v][mo]) {
					visit[v][mo] = true;
					que.push(v);
					que.push(mo);
				}
			}
		}
	}
	int ans = -1;
	check_min(ans, dist[t][0]);
	check_min(ans, dist[t][1]);
	cout << ans << endl;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			vec[a].push_back(make_pair(b, 0));
			vec[b].push_back(make_pair(a, 1));
		}
		int s, t;
		scanf("%d%d", &s, &t);
		solve(s, t);
	}
	return 0;
}
