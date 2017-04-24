#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int N = 111;
vector<pair<int, int> > vec[N];
int cnt[N];
int son[N];
int apple[N];
long long dp[N][N];
int n;
int q, r;

void dfs(int u, int fa, int w) {
	dp[u][0] = 0;
	cnt[u] = apple[u];
	son[u] = 1;
	for (int i = 0; i < vec[u].size(); i++) {
		int v = vec[u][i].first;
		if (v == fa) continue;
		dfs(v, u, vec[u][i].second);
		son[u] += son[v];
		cnt[u] += cnt[v];
		for (int j = r; j > 0; j--) {
			long long tmp = 1LL << 60;
			for (int k = 0; k <= j; k++) {
				tmp = min(tmp, dp[v][k] + dp[u][j - k]);
			}
			dp[u][j] = tmp;
		}
		dp[u][0] += dp[v][0];
	}
	for (int i = r; i >= 1; i--) {
		dp[u][i] = min(dp[u][i], dp[u][i - 1]);
	}
	for (int i = 0; i <= r; i++) {
		dp[u][i] += abs(1LL * son[u] * q + i - cnt[u]) * 1LL * w;
	}
}

int main() {
	while (~scanf("%d", &n)) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			vec[i].clear();
			scanf("%d", &apple[i]);
			sum += apple[i];
		}
		q = sum / n, r = sum % n;
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			vec[a].push_back(make_pair(b, c));
			vec[b].push_back(make_pair(a, c));
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= r; j++) {
				dp[i][j] = 1LL << 60;
			}
		}
		dfs(0, -1, 1LL << 30);
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= r; j++) {
				cout << dp[i][j] << " ";
			}
			cout << endl;
		}
		*/
		cout << dp[0][r] << endl;
	}
	return 0;
}
