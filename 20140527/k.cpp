#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int M = 70;
int n;
long long a[N], b[N];
int cnt[N], len[N];
int dp[N][M];
pair<int, int> pre[N][M];
vector<pair<int, int> > path;

void count_ones(int i, long long x) {
	cnt[i] = 0;
	len[i] = 0;
	while (x) {
		len[i]++;
		cnt[i] += (x & 1);
		x >>= 1;
	}
}

void get_path(int a, int b) {
	if (a == 0) return;
	get_path(a - 1, pre[a][b].first);
	path.push_back(pre[a][b]);
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		count_ones(i, a[i]);
	}
	memset(dp, 0, sizeof(dp));
	memset(pre, -1, sizeof(pre));
	dp[0][0] = 1;
	int m = *max_element(len, len + n);
	//cout << m << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (!dp[i][j]) continue;
			int min_overcap = 0;
			if (j + cnt[i] > m) min_overcap = cnt[i] - (m - j);
			for (int k = min_overcap; k <= j && k <= cnt[i]; k++) {
				dp[i + 1][j + cnt[i] - 2 * k] = 1;
				pre[i + 1][j + cnt[i] - 2 * k] = pair<int, int>(j, k);
			}
		}
	}
	bool valid = dp[n][0];
	if (valid) {
		path.clear();
		get_path(n, 0);
		long long now = 0;
		for (int i = 0; i < path.size(); i++) {
			int crash = path[i].second;
			int other = cnt[i] - crash;
			for (int j = 0; j < m; j++) {
				if (now >> j & 1) {
					if (crash) {
						b[i] ^= (1LL << j);
						now ^= (1LL << j);
						crash--;
					}
				} else {
					if (other) {
						b[i] ^= (1LL << j);
						now ^= (1LL << j);
						other--;
					}
				}
			}
		   	//cout << path[i].first << " " << path[i].second << endl;
	   	}		
		for (int i = 0; i < n; i++) {
			cout << b[i];
			if (i == n - 1) cout << endl;
			else cout << ' ';
		}
	} else {
		puts("impossible");
	}
	return 0;
}
