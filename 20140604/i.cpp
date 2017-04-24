#include <bits/stdc++.h>
using namespace std;

const int N = 111111;
vector<int> vec[N];
int dp[N][3];
int n;

void dfs(int u, int fa) {
	int son = 0;
	int sum = 0;
	int t1 = INT_MAX, t2 = INT_MAX;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i];
		if (v == fa) continue;
		son++;
		dfs(v, u);
		sum += *min_element(dp[v], dp[v] + 3);
		int t = *min_element(dp[v], dp[v] + 2) - *min_element(dp[v], dp[v] + 3);
		if (t < t1) t2 = t1, t1 = t;
		else if (t < t2) t2 = t;
	}
	dp[u][0] = sum + son;
	if (son >= 1) dp[u][1] = sum + son - 1 + t1;
	if (son >= 2) dp[u][2] = sum + son - 2 + t1 + t2;
}

int main() {
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			dp[i][j] = INT_MAX;
		}
	}
	dfs(1, 0);
	int ans = *min_element(dp[1], dp[1] + 3) + 1;
	cout << ans << endl;
	return 0;
}
