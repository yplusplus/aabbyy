#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 11111;
int n, m, r;
pair<int, int> dp[N];

#define MP(x, y) make_pair(x, y)

void update(pair<int, int> &a, pair<int, int> b) {
	if (b.first > a.first || (b.first == a.first && b.second > a.second)) {
		a = b;
	}
}

int main() {
	while (cin >> n >> m >> r) {
		memset(dp, -1, sizeof(dp));
		dp[0] = MP(0, m);
		for (int i = 1; i < r && i <= n; i++) {
			dp[i] = MP(max(i, m), min(i, m));
		}
		dp[r] = MP(r, m);
		for (int i = r + 1; i <= n; i++) {
			for (int j = 1; j <= r; j++) {
				update(dp[i], MP(i + m - dp[i - j].first - dp[i - j].second, dp[i - j].second));
			}
		}
		cout << dp[n].first << " " << n + m - dp[n].second - dp[n].first << endl;
	}
	return 0;
}

