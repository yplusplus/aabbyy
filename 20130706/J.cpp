#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
const int mod = 1000000007;
int dp[N][2],sum[N][2];//blue 0, red 1
int f[N];

int main()
{
	f[0] = 1;
	for(int i = 1; i < N; i ++) f[i] = f[i - 1] * 2 % mod;
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		for(int i = 0; i <= n; i ++)
			dp[i][0] = dp[i][1] = sum[i][0] = sum[i][1] = 0;
		if(m == 1) {
			printf("%d\n",f[n] - 1);
			continue;
		}
		dp[0][0] = dp[0][1] = 1;
		sum[0][0] = sum[0][1] = 1;
		for(int i = 1; i <= n; i ++) {
			dp[i][0] = sum[i - 1][1];
			if(i < m) dp[i][1] = sum[i - 1][0];
			else dp[i][1] = sum[i - 1][0] - sum[i - m][0];
			if(dp[i][1] < 0) dp[i][1] += mod;
			sum[i][1] = (sum[i - 1][1] + dp[i][1]) % mod;
			sum[i][0] = (sum[i - 1][0] + dp[i][0]) % mod;
		}
		int ans = f[n] - dp[n][0] - dp[n][1];
		if(ans < 0) ans = (ans % mod + mod) % mod;
		printf("%d\n",ans);
	}
	return 0;
}

	
