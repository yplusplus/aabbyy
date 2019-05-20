#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 205;
const int mod = 1e9 + 7;

int powmod(int a, int k)
{
	int ret = 1;
	while (k) {
		if (k & 1) ret = 1LL * ret * a % mod;
		a = 1LL * a * a % mod;
		k >>= 1;
	}
	return ret;
}

int f[N];
int c[N][N];
int lg[N][2 * N];

void Init()
{
	f[0] = 1;
	for (int i = 1; i < N; i++) {
		f[i] = 1LL * f[i - 1] * i % mod;
	}

	c[0][0] = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || i == j) c[i][j] = 1;
			else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
		}
	}

	for (int i = 0; i < N; i++) {
		lg[i][0] = 1;
		for (int j = 1; j < 2 * N; j++) {
			lg[i][j] = 1LL * lg[i][j - 1] * i % mod;
		}
	}
}

int n, k;
int dp[N][N];
int sum[N][N];

int main()
{
	Init();

	int T;
	cin >> T;
	while (T --) {
		cin >> n >> k;

		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));
		dp[0][0] = 1;
		for (int j = 0; j <= k; j++) {
			sum[0][j] = 1;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= k; j++) {
				sum[i][j] = sum[i][j - 1];

				int other = 1;
				for (int t = 1; t <= i; t++) {
					other = 1LL * other * lg[j - 1][2 * (n - i + t - 1)] % mod;
					int tmp = 1LL * c[n - (i - t)][t] * c[n - (i - t)][t] % mod;
					tmp = 1LL * tmp * f[t] % mod;
					tmp = 1LL * tmp * other % mod;

					dp[i][j] += 1LL * sum[i - t][j - 1] * tmp % mod;
					dp[i][j] %= mod;
				}
				sum[i][j] = (sum[i][j] + dp[i][j]) % mod;

				//printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
			}
		}

		for (int i = 1; i <= n; i++) {
			int count = 2 * n * i - i * i;
			int mul = powmod(k, n * n - count);
			for (int j = 1; j <= k; j++) {
				dp[i][j] = 1LL * dp[i][j] * mul % mod;
			}
		}

		int res[N];
		res[n + 1] = 0;
		for (int i = 1; i <= n; i++) {
			res[i] = 0;
			for (int j = 1; j <= k; j++) {
				res[i] = (res[i] + dp[i][j]) % mod;
			}
		}

		int ret = 0;
		for (int i = n; i > 0; i--) {
			for (int j = i + 1; j <= n; j++) {
				res[i] = (res[i] - 1LL * c[j][j - i] * res[j] % mod + mod) % mod;
			}
			ret += 1LL * i * i * res[i] % mod;
			ret %= mod;

			//cout << i << " " << res[i] << " " << ret  << endl;
		}

		cout << ret << endl;
	}

	return 0;
}
