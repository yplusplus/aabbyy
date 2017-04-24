#include <bits/stdc++.h>
using namespace std;

const int N = 111;
double p[N];
int w[N];
int n, m, s;
double dp[N];

int main() {
	freopen("casino.in", "r", stdin);
	freopen("casino.out", "w", stdout);
	cin >> n >> m >> s;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x >> w[i];
		p[i] = 1.0 * x / s;
	}
	memset(dp, 0, sizeof(dp));
	for (int i = n + 1; i < N; i++) dp[i] = 1;
	for (int times = 0; times < 10000; times++) {
		for (int i = 1; i <= n; i++) {
			double t = 0;
			for (int j = 0; j < m; j++) {
				t = max(t, dp[i - 1] * (1 - p[j]) + dp[i + w[j]] * p[j]);
			}
            dp[i] = t;
		}
	}
	printf("%.20f\n", dp[n]);
	return 0;
}
