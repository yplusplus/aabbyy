#include <bits/stdc++.h>
using namespace std;

const int N = 26;
bool g[N][N];
int ind[N];
int dp[N];
int pre[N];

bool topo() {
	queue<int> que;
	memset(dp, -1, sizeof(dp));
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i < N; i++) {
		if (ind[i] == 0) {
			que.push(i);
			dp[i] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int v = 0; v < N; v++) {
			if (g[u][v]) {
				if (dp[u] + 1 > dp[v]) {
					dp[v] = dp[u] + 1;
					pre[v] = u;
				}
				if (--ind[v] == 0) {
					que.push(v);
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		if (ind[i]) {
			return false;
		}
	}
	return true;
}

int color[N];

int dfs(int u, int fa) {
	if (color[u] == 2) return -1;
	pre[u] = fa;
	if (color[u] == 1) return u;
	color[u] = 1;
	for (int v = 0; v < N; v++) {
		if (g[u][v]) {
			int ret = dfs(v, u);
			if (ret != -1) return ret;
		}
	}
	color[u] = 2;
	return -1;
}

void solve() {
	if (topo()) {
		vector<char> path;
		int t = -1;
		for (int i = 0; i < N; i++) {
			if (t == -1 || dp[t] < dp[i]) {
				t = i;
			}
		}
		while (t != -1) {
			path.push_back(t + 'a');
			t = pre[t];
		}
		int size = path.size();
		int n = (size + 1) / 2; 
		reverse(path.begin(), path.end());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				putchar(path[(i + j) % size]);
			}
			puts("");
		}
	} else {
		vector<char> circle;
		memset(color, 0, sizeof(color));
		int t;
		for (int i = 0; i < N; i++) {
			t = dfs(i, -1);
			if (t != -1) break;
		}
		int x = pre[t];
		while (x != t) {
			circle.push_back(x + 'a');
			x = pre[x];
		}
		circle.push_back(x + 'a');
		reverse(circle.begin(), circle.end());
		int size = (int)circle.size();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				putchar(circle[(i + j) % size]);
			}
			puts("");
		}
	}
}

int main() {
	int T;
	char str[10];
	scanf("%d", &T);
	while (T--) {
		int m;
		scanf("%d", &m);
		memset(g, true, sizeof(g));
		for (int i = 0; i < N; i++) ind[i] = N;
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			if (!g[str[0] - 'a'][str[1] - 'a']) continue;
			g[str[0] - 'a'][str[1] - 'a'] = false;
			ind[str[1] - 'a']--;
		}
		solve();
	}
	return 0;
}
