#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
const int N = 22;
int d[N];
int n;
bool g[N][N];

vector<pair<int, int> > edges;

bool between(int a, int l, int r) { return a > l && a < r; }

bool check(const pair<int, int> &e) {
	int a = e.first, b = e.second;
	for (int i = 0; i < edges.size(); i++) {
		if (a == edges[i].first || a == edges[i].second || b == edges[i].first || b == edges[i].second) continue;
		bool flag = between(a, edges[i].first, edges[i].second) ^ between(b, edges[i].first, edges[i].second);
		if (flag) return false;
	}
	return true;
}

bool dfs(int now) {
	for (int i = 1; i <= n; i++) {
		if (i == now || d[i] == 0) continue;
		if (g[now][i]) continue;
		pair<int, int> edge = MP(min(now, i), max(now, i));
		if (check(edge)) {
			d[now]--, d[i]--;
			edges.push_back(edge);
			g[now][i] = g[i][now] = 1;
			if (edges.size() == n - 3) return true;
			int id = -1;
			for (int j = 1; j <= n; j++) {
				if (d[j] == 0) continue;
				if (id == -1 || d[id] > d[j]) id = j;
			}
			if (id != -1 && dfs(id)) return true;
			g[now][i] = g[i][now] = 0;
			d[now]++, d[i]++;
			edges.pop_back();
		}
	}
	return false;
}

void solve() {
	int sum = 0;
	bool flag = false;
	for (int i = 1; i <= n; i++) { sum += d[i]; 
		if (d[i] == 0) flag = true;
	}
	if (sum != (n - 2) * 3 || flag) { puts("N"); return; }
	for (int i = 1; i <= n; i++) d[i]--;
	int start = -1;
	for (int i = 1; i <= n; i++) {
		if (d[i] == 0) continue;
		if (start == -1 || d[start] > d[i]) start = i;
	}
	edges.clear();
	memset(g, 0, sizeof(g));
	for (int i = 1; i < n; i++) {
		g[i][i + 1] = g[i + 1][i] = 1;
	}
	g[1][n] = g[n][1] = 1;
	if (!dfs(start)) puts("N");
	else {
		puts("Y");
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = j + 1; k <= n; k++) {
					if (g[i][j] && g[i][k] && g[j][k]) printf("%d %d %d\n", i, j, k);
				}
			}
		}
	}
}

int main() {
	int T, Case;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &Case, &n);
		for (int i = 1; i <= n; i++) { scanf("%d", &d[i]); }
		printf("%d ", Case);
		solve();
	}
	return 0;
}
