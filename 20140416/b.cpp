#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<VB> VVB;
const int UPPERBOUND = 4;
VI value, current(UPPERBOUND);
VVB connected;
VB visited;

void init(int n) {
	value.resize(n + 1);
	connected.clear();
	connected.resize(n + 1, VB(n + 1, 0));
	visited.resize(n + 1);
}

bool check(int k) {
	for (int i = 0; i < k; ++i) {
		for (int j = i + 1; j < k; ++j) {
			if (connected[current[i]][current[j]]) continue;
			return 0;
		}
	}
	return 1;
}

int answer;
void dfs(int n, int k, int sum) {
	if (!check(k)) return ;
	answer = max(sum, answer);
	if (k >= n || k >= 4) return ;
	for (int i = 1; i <= n; ++i) {
		if (visited[i]) continue;
		current[k] = i;
		visited[i] = 1;
		dfs(n, k + 1, sum + value[i]);
		visited[i] = 0;
	}
}

int run() {
	int n, m;
	while (cin >> n >> m) {
		init(n);
		for (int i = 1; i <= n; ++i) cin >> value[i];
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) connected[i][j] = 0;
		for (int i = 1; i <= n; ++i) visited[i] = 0;
		int x, y;
		for (int i = 1; i <= m; ++i) {
			cin >> x >> y;
			connected[x][y] = connected[y][x] = 1;
		}
		answer = 0;
		dfs(n, 0, 0);
		cout << answer << endl;
	}
	return 0;
}

int main() {
	//freopen("in_b", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
