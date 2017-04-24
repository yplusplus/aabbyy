#include <bits/stdc++.h>
using namespace std;

const int N = 2222;
int n;
bool visit[N];
int x[N], y[N];
int g[N][N];
int fa[N];
int dep[N];

void dfs(int u, int d, int pre) {
	dep[u] = d;
	visit[u] = true;
	fa[u] = pre;
	for (int v = 0; v < n; v++) {
		if (!visit[v] && g[u][v]) {
			dfs(v, d + 1, u);
		}
	}
}

void solve() {
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (x[i] == x[j] || y[i] == y[j]) {
				g[i][j] = g[j][i] = 1;
			}
		}
	}
	memset(visit, false, sizeof(visit));
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (!visit[i]) {
			ans++;
			dfs(i, 0, -1);
		}
	}
	cout << ans << endl;
	vector<pair<int, int> > vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(make_pair(dep[i], i));
	}
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < n; i++) {
		if (vec[i].first == 0) break;
		int u = vec[i].second;
		int v = fa[u];
		printf("(%d, %d) ", x[u], y[u]);
		if (x[u] == x[v]) {
			if (y[u] > y[v]) puts("DOWN");
			else puts("UP");
		} else {
			if (x[u] > x[v]) puts("LEFT");
			else puts("RIGHT");
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x[i], &y[i]);
		}
		solve();
	}
	return 0;
}
