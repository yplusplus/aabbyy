#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
const int mod = 998244353;

int sum[N], dp[N];
int lg[N];

void Init()
{
	lg[0] = 1;
	for (int i = 1; i < N; i++) {
		lg[i] = 1LL * lg[i - 1] * 10 % mod;
	}

	sum[0] = 0;
	for (int i = 1; i < N; i++) {
		sum[i] = 1LL * sum[i - 1] * 100 % mod;
		int tmp = 1LL * 45 * lg[i - 1] % mod; 
		sum[i] = (sum[i] + tmp) % mod;
	}

	int tot_dp = 0;

	dp[0] = 0;
	for (int i = 1; i < N; i++) {
		dp[i] = 2LL * tot_dp  % mod;
		dp[i] = (dp[i] + sum[i]) % mod;

		tot_dp = 10LL * (tot_dp + dp[i - 1]) % mod;
	}

	/*
	for (int i = 1; i < N; i++) {
		cout << i << " " << sum[i] << " " << dp[i] << endl;
	}
	*/
}

int main()
{
	Init();

	int T;
	cin >> T;
	while (T --) {
		int n;
		cin >> n;
		cout << dp[n] << endl;
	}
	return 0;
}
