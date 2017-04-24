#include <bits/stdc++.h>
using namespace std;

const int N = 11111;
vector<pair<int, int> > vec[N];
int val[N];
bool visit[N];
int n, m;

void solve() {
	deque<int> que;
	for (int i = 1; i <= n; i++) {
		que.push_back(i);
		visit[i] = true;
	}
	while (!que.empty()) {
		int u = que.front(); que.pop_front();
		visit[u] = false;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first, w = vec[u][i].second;
			if (val[u] + val[v] < val[w]) {
				val[w] = val[u] + val[v];
				if (!visit[w]) {
					visit[w] = true;
					if (que.empty() || val[w] > val[que.front()]) que.push_back(w);
					else que.push_front(w);
				}
			}
		}
	}
	printf("%d\n", val[1]);
}

int main() {
	freopen("dwarf.in", "r", stdin);
	freopen("dwarf.out", "w", stdout);
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) { scanf("%d", &val[i]); vec[i].clear(); }
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[b].push_back(pair<int, int>(c, a));
			vec[c].push_back(pair<int, int>(b, a));
		}
		solve();
	}
	return 0;
}
