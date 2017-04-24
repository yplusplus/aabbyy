#include <bits/stdc++.h>
using namespace std;

const int N = 2555;
const int M = 25555;
vector<int> vec[N];
pair<int, int> e[M];
int g[N][N];
bool visit[N];
int n, m, s;
int alloc;

void bfs(int s) {
	for (int i = 1; i <= n; i++) {
		visit[i] = false;
	}
	queue<int> que;
	que.push(s);
	visit[s] = true;
	alloc = 1;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i];
			if (!visit[v]) {
				g[u][v] = g[v][u] = alloc++;
				que.push(v);
				visit[v] = true;
			}
		}
	}
}

void solve() {
	memset(g, 0, sizeof(g));
	bfs(s);
	for (int i = 1; i <= m; i++) {
		int a = e[i].first, b = e[i].second;
		printf("%d %d ", a, b);
		if (g[a][b]) printf("%d\n", g[a][b]);
		else printf("%d\n", alloc++);
		//cout << alloc << endl;
	}
}

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &s);
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(b);
			vec[b].push_back(a);
			e[i] = make_pair(a, b);
		}
		//cout << 123 << endl;
		printf("Case %d:\n", Case++);
		solve();
	}
	return 0;
}
