#include <bits/stdc++.h>
using namespace std;

const int N = 1111111;
double dp[N];
double sum[N];
int n, k;

int main() {
	int T, Case = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		dp[0] = 0;
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; i++) {
			dp[i] = 0;
			dp[i] += i;
			if (i - k - 1 >= 0) dp[i] += 2 * sum[i - k - 1];
			dp[i] /= i;
			sum[i] = sum[i - 1] + dp[i];
		}
		printf("Case #%d: %.4f\n", Case++, dp[n]);
	}
	return 0;
}
