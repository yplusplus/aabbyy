#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int T = 255;
const int inf = 1 << 30;
int ti[N];
vector<int> forward, backward;
int dp[N][T];
int n, t, m1, m2;

void check_min(int &a, int b) {
	a = min(a, b);
}

void update(int x, int pos, int need, int cur_time, int has_wait) {
	if (x < cur_time) return;
	int q = ti[n - 1] * 2;
	if (x < cur_time) {
		int delta = cur_time - x;
		x += (delta + q - 1) / q * q;
	}
	int wait = x - cur_time;
	x += need;
	if (x <= t) {
		check_min(dp[pos][x], has_wait + wait);
	}
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= t; j++) {
			dp[i][j] = inf;
		}
	}
	dp[1][0] = 0;
	for (int j = 0; j < t; j++) {
		for (int i = 1; i <= n; i++) {
			if (dp[i][j] == inf) continue;
			for (int k = 0; k < m1; k++) {
				//right
				if (i < n) update(forward[k] + ti[i - 1], i + 1, ti[i] - ti[i - 1], j, dp[i][j]);
				//left
				//if (i > 1) update(forward[k] + 2 * ti[n - 1] - ti[i - 1], i - 1, ti[i - 1] - ti[i - 2], j, dp[i][j]);
			}
			for (int k = 0; k < m2; k++) {
				//right
				//if (i < n) update(backward[k] + ti[n - 1] + ti[i - 1], i + 1, ti[i] - ti[i - 1], j, dp[i][j]);
				//left
				if (i > 1) update(backward[k] + ti[n - 1] - ti[i - 1], i - 1, ti[i - 1] - ti[i - 2], j, dp[i][j]);
			}
		}
	}
	int ans = inf;
	for (int i = 0; i <= t; i++) {
		if (dp[n][i] < inf) check_min(ans, dp[n][i] + t - i);
	}
	if (ans == inf) puts("impossible");
	else printf("%d\n", ans);
}

int main() {
	int Case = 1;
	while (~scanf("%d", &n), n) {
		forward.clear();
		backward.clear();
		scanf("%d", &t);
		for (int i = 1; i < n; i++) { scanf("%d", &ti[i]); }
		ti[0] = 0;
		for (int i = 1; i < n; i++) ti[i] += ti[i - 1];
		scanf("%d", &m1);
		for (int i = 0, x; i < m1; i++) {
			scanf("%d", &x);
			forward.push_back(x);
		}
		scanf("%d", &m2);
		for (int i = 0, x; i < m2; i++) {
			scanf("%d", &x);
			backward.push_back(x);
		}
		printf("Case Number %d: ", Case++);
		solve();
	}
	return 0;
}
