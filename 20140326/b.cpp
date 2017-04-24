#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PI2;
typedef vector<PI2> VI2;
#define x first
#define y second

const int K = 26;
VI2 cost[K];

int work(const string &buf, int n) {
	VI dp(n + 1, INT_MAX);
	dp[0] = 0;
	int len = buf.length(), idx;
	for (int i = 0; i < len; ++i) {
		for (int j = n; j > 0; --j) {
			if (dp[j - 1] == INT_MAX) continue;
			int sum = 0;
			idx = buf[i] - 'a';
			for (int k = 0, sz = cost[idx].size(); k < sz; ++k) {
				if (j % cost[idx][k].x) continue;
				sum += j / cost[idx][k].x * cost[idx][k].y;
			}
			dp[j] = min(dp[j - 1] + sum, dp[j]);
		}
		//for (int j = 0; j <= n; ++j) cout << dp[j] << ' '; cout << endl;
	}
	return dp[n];
}

int run() {
	int _;
	cin >> _;
	for (int cas = 1; cas <= _; ++cas) {
		string buf;
		int n;
		cin >> buf >> n;
		for (int i = 0; i < K; ++i) {
			int k;
			cin >> k;
			cost[i].resize(k);
			for (int j = 0; j < k; ++j) cin >> cost[i][j].x >> cost[i][j].y;
		}
		cout << "Case #" << cas << ": " << work(buf, n) << endl;
	}
	return 0;
}

int main() {
	//freopen("in_b", "r", stdin);
	ios::sync_with_stdio(0);
	return run();
}
