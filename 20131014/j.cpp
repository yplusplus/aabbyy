#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
vector<pair<int, int> > vec[N];
int n, m;

int dp[N][3];
void dfs(int u, int fa) {
	dp[u][0] = 0;
	dp[u][1] = 1;
	dp[u][2] = 0;
	bool isleaf = true;
	int t = N;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		isleaf = false;
		dfs(v, u);
		dp[u][0] += max(dp[v][0], dp[v][2]);
		t = min(t, max(dp[v][0], dp[v][2]) - dp[v][1]);
	}
	if (!isleaf) {
		dp[u][1] += dp[u][0];
		dp[u][2] = dp[u][0] - t;
	} else {
		dp[u][0] = 0;
		dp[u][1] = 1;
		dp[u][2] = -N;
	}
}

vector<pair<int, int> > path;
pair<int, int> edge[N];

void find_path(int u, int s, int fa) {
	if (s == 0 || s == 1) {
		for (int i = 0; i <  vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (v == fa) continue;
			if (dp[v][2] > dp[v][0]) find_path(v, 2, u);
			else find_path(v, 0, u);
		}
	} else if (s == 2) {
		int t = N;
		int id = -1;
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (v == fa) continue;
			int tmp = max(dp[v][0], dp[v][2]) - dp[v][1];
			if (tmp < t) {
				t = tmp;
				id = vec[u][i].second;
			}
		}
		path.push_back(edge[id]);
		for (int i = 0; i < vec[u].size(); i++) {
			int v = vec[u][i].first;
			if (v == fa) continue;
			if (v == edge[id].first || v == edge[id].second) find_path(v, 1, u);
			else if (dp[v][2] > dp[v][0]) find_path(v, 2, u);
			else find_path(v, 0, u);
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) vec[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			edge[i] = make_pair(a, b);
			vec[a].push_back(make_pair(b, i));
			vec[b].push_back(make_pair(a, i));
		}
		dfs(1, 0);
		int ans = max(dp[1][0], dp[1][2]);
		path.clear();
		if (ans == dp[1][0]) {
			find_path(1, 0, 0);
		} else {
			find_path(1, 2, 0);
		}
		cout << path.size() << endl;
		for (int i = 0; i < path.size(); i++) {
			cout << path[i].first << " " << path[i].second << endl;
		}
	}
	return 0;
}

