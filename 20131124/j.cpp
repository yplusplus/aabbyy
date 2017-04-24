#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 222;
double dp[11111][N];
double t[N][N];
int n;
int main() {
	while (~scanf("%d", &n)) {
		int nn = n * (n - 1) * (n - 2) / 6;
		for (int i = 0; i < nn; i++) {
			for (int j = 0; j < nn; j++) {
				scanf("%lf", &t[i][j]);
			}
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < nn; i++) dp[0][i] = 1.0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int id;
			scanf("%d", &id);
			for (int j = 0; j < nn; j++) {
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] * t[j][id]);
				dp[i + 1][id] = max(dp[i + 1][id], dp[i][j] * t[j][id]);
			}
		}
		double ans = *max_element(dp[n], dp[n] + nn);
		printf("%.8f\n", ans);
	}
	return 0;
}
