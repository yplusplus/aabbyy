#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 1111;
int dp[N][N];
int a[N], f[N];
int sum[N];
const int inf = 1 << 30;
int n, m, l;

void read(int &x) {
	x = 0;
	char ch;
	ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		x = 10 * x + ch - '0';
		ch = getchar();
	}
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &l)) {
		sum[0] = 0;
		for (int i = 1; i <= n; i++) read(a[i]), sum[i] = sum[i - 1] + a[i];

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				dp[i][j] = -inf;
			}
			//dp[i][0] = sum[i];
		   	f[i] = -inf;
		}
		dp[0][0] = 0;

		for (int i = 1; i <= n; i++) {
			if (i - l >= 0) {
				for (int j = 0; j <= i - l; j++) {
					f[j] = max(f[j], dp[i - l][j] - sum[i - l]);
				}
			}
			for (int j = 0; j <= i; j++) {
				if (j >= 1) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
				dp[i][j] = max(dp[i][j], sum[i] + f[j]);
				//cout << dp[i][j] << " ";
			}
			//cout << endl;
		}
		int ans = -inf;
		for (int i = m; i <= n; i++) {
			ans = max(ans, dp[n][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}